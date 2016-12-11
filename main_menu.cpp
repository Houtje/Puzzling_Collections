#include "main_menu.h"
#include "help_screen.h"
#include "browse_screen.h"
#include "select_and_play.h"
#include "puzzle.h"
#include "difficulty_screen.h"

#define ALL_IMAGES 11
#define SCREEN_H 900
#define SCREEN_W 1600

// Constructor
Main_Menu::Main_Menu()
{
    table = NULL;
    widget = NULL;
}

// Destructor
Main_Menu::~Main_Menu(){

}

// Goes to one of the screens.
void Main_Menu::toScreen(Screen s){
    switch(s){
        case SC_HELP: {
            Help_Screen *h = new Help_Screen();
            h->init();
            widget->close();
        } break;
        case SC_BROWSE: {
            Browse_Screen *b = new Browse_Screen(0);
            b->init();
            widget->close();
        } break;
        case SC_SELECT: {
            Select_And_Play *s = new Select_And_Play(0);
            s->init();
            widget->close();
        } break;
        case SC_QUICK: {
            Puzzle *p = new Puzzle();
            /*
            QPushButton *p1 = new QPushButton(tr("&Normal Mode"));
            QPushButton *p2 = new QPushButton(tr("&Hard Mode"));
            QMessageBox box;
            box.addButton(p1, QMessageBox::ActionRole);
            box.addButton(p2, QMessageBox::ActionRole);
            box.setText("What mode would you like to play?");
            box.exec();
            if(box.clickedButton() == p1)
             */
                p->initNM(rand() % ALL_IMAGES, NULL);
            /*
            else if(box.clickedButton() == p2)
                p->initHM(rand() % ALL_IMAGES);
             */
        } break;
    }
}

// Starts several subprograms.
void Main_Menu::onTableClicked(const QModelIndex &i)
{
    if(i.row() == 0 && i.column() == 2)
        toScreen(SC_HELP);
    else if(i.row() == 2 && i.column() == 0)
        toScreen(SC_BROWSE);
    else if(i.row() == 2 && i.column() == 1)
        toScreen(SC_SELECT);
    else if(i.row() == 2 && i.column() == 2)
        toScreen(SC_QUICK);
}

// Creates the main menu model to be used in the table.
QStandardItemModel *Main_Menu::createModel(){
    QStandardItemModel *model = new QStandardItemModel(4,3);
    QColor color(0,0,255,50);

    QStandardItem *item1 = new QStandardItem();
    QFont font1;
    font1.setPixelSize(50);
    item1->setFont(font1);
    item1->setTextAlignment(Qt::AlignCenter);
    item1->setData(QVariant(color), Qt::BackgroundRole);
    item1->setText("Browse");
    model->setItem(2, 0, item1);

    QStandardItem *item2 = item1->clone();
    item2->setText("Select and Play");
    model->setItem(2, 1, item2);

    QStandardItem *item3 = item1->clone();
    item3->setText("Quick Puzzle");
    model->setItem(2, 2, item3);

    QStandardItem *item4 = item1->clone();
    QFont font2;
    font2.setPixelSize(100);
    item4->setFont(font2);
    item4->setText("?");
    model->setItem(0, 2, item4);

    QStandardItem *item5 = item1->clone();
    QFont font3;
    font3.setPixelSize(50);
    font3.setItalic(true);
    item5->setFont(font3);
    item5->setText("Puzzling Collections Main Menu");
    model->setItem(0, 1, item5);

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


// Initializes the main menu.
void Main_Menu::init(){
           widget = new QWidget();

           table = new QTableView(widget);
           table->setModel(createModel());
           table->verticalHeader()->hide();
           table->horizontalHeader()->hide();
           for(int i = 0; i < 4; i++)
               table->setRowHeight(i, 225);
           for(int i = 0; i < 3; i++)
               table->setColumnWidth(i, 533);
           table->resize(SCREEN_W+25, SCREEN_H+14);

           QPalette palette = table->palette();
           QColor color(0,0,255,50);
           palette.setBrush(QPalette::Highlight,QBrush(color));
           palette.setBrush(QPalette::HighlightedText,QBrush(Qt::black));
           table->setPalette(palette);
           table->setFocusPolicy(Qt::NoFocus);

           this->connect(table, SIGNAL(clicked(QModelIndex)), SLOT(onTableClicked(QModelIndex)));

           widget->setWindowTitle("Puzzling Collections");
           widget->resize(SCREEN_W, SCREEN_H-1);
           widget->show();
}
