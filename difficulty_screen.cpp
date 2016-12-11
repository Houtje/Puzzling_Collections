#include "difficulty_screen.h"
#include "help_screen.h"
#include "main_menu.h"
#include "puzzle.h"
#include "browse_screen.h"

#define ALL_IMAGES 11
#define SCREEN_H 900
#define SCREEN_W 1600

// Constructor
Difficulty_Screen::Difficulty_Screen(int image)
{
    table = NULL;
    widget = NULL;
    clickedImage = image;
}

// Destructor
Difficulty_Screen::~Difficulty_Screen(){

}

// Converts an integer to a string.
QString Difficulty_Screen::ItoS(int number)
{
  std::ostringstream oss;
  oss << number;
  return QString::fromStdString(oss.str());
}

// Gets the full image at the number specified.
QImage *Difficulty_Screen::getFullImage(int number){
    if(number >= 0 && number < ALL_IMAGES){
        QString str = QDir::currentPath() + "/../Naturalis/";
        str += ItoS(number);
        str += ".png";
        QImage *image = new QImage(str);
        return image;
    }
    return NULL;
}

// Goes to one of the screens.
void Difficulty_Screen::toScreen(Screen s){
    switch(s){
        case SC_BROWSE: {
            Browse_Screen *b = new Browse_Screen(0);
            b->init();
            widget->close();
        } break;
        case SC_PUZZLE_NM: {
            Puzzle *p = new Puzzle();
            p->initNM(clickedImage, NULL);
        } break;
        case SC_PUZZLE_HM: {
            Puzzle *p = new Puzzle();
            p->initHM(clickedImage);
        } break;
    }
}

// Starts several subprograms.
void Difficulty_Screen::onTableClicked(const QModelIndex &i)
{
    if(i.row() == 0 && i.column() == 2)
        toScreen(SC_BROWSE);
    if(i.row() == 2 && i.column() == 0)
        toScreen(SC_PUZZLE_NM);
    if(i.row() == 2 && i.column() == 1)
        toScreen(SC_PUZZLE_HM);
}

// Creates the browse screen model to be used in the table.
QStandardItemModel *Difficulty_Screen::createModel(){
    QStandardItemModel *model = new QStandardItemModel(4,3);
    QColor color(0,0,255,50);

    QStandardItem *item1 = new QStandardItem();
    QFont font1;
    font1.setPixelSize(100);
    item1->setFont(font1);
    item1->setTextAlignment(Qt::AlignCenter);
    item1->setData(QVariant(color), Qt::BackgroundRole);
    item1->setText("<-");
    model->setItem(0, 2, item1);

    QStandardItem *item2 = new QStandardItem();
    QImage image = *getFullImage(clickedImage);
    image = image.scaled(SCREEN_W/3, SCREEN_H/4);
    item2->setData(QVariant(QPixmap::fromImage(image)), Qt::DecorationRole);
    item2->setData(QVariant(color), Qt::BackgroundRole);
    item2->setSelectable(false);
    model->setItem(1, 0, item2);

    QStandardItem *item3 = item1->clone();
    QFont font2;
    font2.setPixelSize(50);
    font2.setItalic(true);
    item3->setFont(font2);
    item3->setText("Puzzling Collections Difficulty Screen");
    model->setItem(0, 1, item3);

    QStandardItem *item4 = item1->clone();
    QFont font3;
    font3.setPixelSize(50);
    font3.setBold(true);
    item4->setFont(font3);
    item4->setText("You chose this picture.");
    model->setItem(1, 1, item4);

    QStandardItem *item5 = item1->clone();
    QFont font4;
    font4.setPixelSize(50);
    item5->setFont(font4);
    item5->setText("Normal Mode");
    model->setItem(2, 0, item5);

    QStandardItem *item6 = item5->clone();
    item6->setText("Hard Mode");
    model->setItem(2, 1, item6);

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
void Difficulty_Screen::init(){
    widget = new QWidget();

    table = new QTableView(widget);
    table->setModel(createModel());
    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();

    for(int i = 0; i < 4; i++)
       table->setRowHeight(i, 225);
    for(int i = 0; i < 3; i++)
       table->setColumnWidth(i, 533);
    table->resize(SCREEN_W+25,SCREEN_H+14);

    QPalette palette = table->palette();
    QColor color(0,0,255,50);
    palette.setBrush(QPalette::Highlight,QBrush(color));
    palette.setBrush(QPalette::HighlightedText,QBrush(Qt::black));
    table->setPalette(palette);
    table->setFocusPolicy(Qt::NoFocus);

    this->connect(table, SIGNAL(clicked(QModelIndex)), SLOT(onTableClicked(QModelIndex)));

    widget->setWindowTitle("Puzzling Collections");
    widget->resize(SCREEN_W,SCREEN_H-1);
    widget->show();
}
