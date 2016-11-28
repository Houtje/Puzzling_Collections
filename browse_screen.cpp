#include "browse_screen.h"
#include "help_screen.h"
#include "main_menu.h"
#include "puzzle.h"
#include "difficulty_screen.h"

#define ALL_IMAGES 5

// Constructor
Browse_Screen::Browse_Screen(int block)
{
    table = NULL;
    widget = NULL;
    imgBlock = block;
    clickedImage = 0;
}

// Destructor
Browse_Screen::~Browse_Screen(){

}

// Converts an integer to a string.
QString Browse_Screen::ItoS(int number)
{
  std::ostringstream oss;
  oss << number;
  return QString::fromStdString(oss.str());
}

// Gets the full image at the number specified.
QImage *Browse_Screen::getFullImage(int number){
    if(number >= 0 && number < ALL_IMAGES){
        QString str = QDir::currentPath();
        str += "/../Puzzling_Collections-master/images/";
        str += ItoS(number);
        str += ".jpg";
        QImage *image = new QImage(str);
        return image;
    }
    return NULL;
}

// Goes to one of the screens.
void Browse_Screen::toScreen(Screen s){
    switch(s){
        case SC_MAIN: {
            Main_Menu *m = new Main_Menu();
            m->init();
            widget->close();
        } break;
        case SC_DIFF: {
            Difficulty_Screen *d = new Difficulty_Screen(clickedImage);
            d->init();
            widget->close();
        } break;
    }
}

// Starts several subprograms.
void Browse_Screen::onTableClicked(const QModelIndex &i)
{
    if(i.row() == 0 && i.column() == 2)
        toScreen(SC_MAIN);
    else if(i.row() == 0 && i.column() == 0){
        imgBlock++;
        table->setModel(createModel());
    }
    else if(i.row() == 3 && i.column() == 0){
        imgBlock--;
        table->setModel(createModel());
    }
    else if((i.row() == 1 && i.column() == 1)
    || (i.row() == 1 && i.column() == 2)
    || (i.row() == 2 && i.column() == 1)
    || (i.row() == 2 && i.column() == 2)){
        clickedImage = (imgBlock*4)+(((i.row()-1)*2)+(i.column()-1));
        QImage *image = getFullImage(clickedImage);
        if(image != NULL){
            QPushButton *p1 = new QPushButton(tr("&Zoom"));
            QPushButton *p2 = new QPushButton(tr("&Puzzle"));
            QMessageBox box;
            box.addButton(p1, QMessageBox::ActionRole);
            box.addButton(p2, QMessageBox::ActionRole);
            box.setText("What do you want to do with this picture?");
            box.exec();
            if(box.clickedButton() == p1){
                QLabel *label = new QLabel();
                label->setPixmap(QPixmap::fromImage(*image));
                label->resize(1600,900);
                label->show();
            }
            else if(box.clickedButton() == p2){
                toScreen(SC_DIFF);
            }
        }
    }
}

// Creates the browse screen model to be used in the table.
QStandardItemModel *Browse_Screen::createModel(){
    QStandardItemModel *model = new QStandardItemModel(4,3);
    QColor color(0,0,255,50);

    QStandardItem *item1 = new QStandardItem();
    QFont font1;
    font1.setPixelSize(100);
    item1->setFont(font1);
    item1->setTextAlignment(Qt::AlignCenter);
    item1->setData(QVariant(color), Qt::BackgroundRole);
    item1->setText("/\\");
    model->setItem(0, 0, item1);

    QStandardItem *item2 = item1->clone();
    item2->setText("\\/");
    model->setItem(3, 0, item2);

    QStandardItem *item3 = item1->clone();
    item3->setText("<-");
    model->setItem(0, 2, item3);

    QStandardItem *item4 = item1->clone();
    QFont font2;
    font2.setPixelSize(50);
    font2.setItalic(true);
    item4->setFont(font2);
    item4->setText("Puzzling Collections Browse Screen");
    model->setItem(0, 1, item4);

    for(int i = imgBlock*4; i < (imgBlock*4)+4; i++){
        QStandardItem *item5 = new QStandardItem();
        QImage *image = getFullImage(i);
        if(image != NULL){
            item5->setData(QVariant(QPixmap::fromImage(*image)), Qt::DecorationRole);
            item5->setData(QVariant(color), Qt::BackgroundRole);
            item5->setSelectable(false);
            if(i == imgBlock*4)
                model->setItem(1, 1, item5);
            else if(i == (imgBlock*4)+1)
                model->setItem(1, 2, item5);
            else if(i == (imgBlock*4)+2)
                model->setItem(2, 1, item5);
            else if(i == (imgBlock*4)+3)
                model->setItem(2, 2, item5);
        }
    }

    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 3; ++column) {
            QStandardItem *item;
            if(model->item(row, column) == NULL){
                item = new QStandardItem();
                item->setData(QVariant(color), Qt::BackgroundRole);
            }
            else
                item = model->item(row, column)->clone();
            item->setSelectable(false);
            model->setItem(row, column, item);
        }
    }

    return model;
}


// Initializes the browse screen.
void Browse_Screen::init(){
    widget = new QWidget();

    table = new QTableView(widget);
    table->setModel(createModel());
    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();

    for(int i = 0; i < 4; i++)
       table->setRowHeight(i, 225);
    for(int i = 0; i < 3; i++)
       table->setColumnWidth(i, 533);
    table->resize(1625,914);

    QPalette palette = table->palette();
    QColor color(0,0,255,50);
    palette.setBrush(QPalette::Highlight,QBrush(color));
    palette.setBrush(QPalette::HighlightedText,QBrush(Qt::black));
    table->setPalette(palette);
    table->setFocusPolicy(Qt::NoFocus);

    this->connect(table, SIGNAL(clicked(QModelIndex)), SLOT(onTableClicked(QModelIndex)));

    widget->setWindowTitle("Puzzling Collections");
    widget->resize(1600,899);
    widget->show();
}
