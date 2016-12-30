#include "main_menu.h"
#include "help_screen.h"
#include "browse_screen.h"
#include "select_and_play.h"
#include "puzzle.h"
#include "difficulty_screen.h"
#include "windows.h"

#define ALL_IMAGES 11
#define SCREEN_H 1080
#define SCREEN_W 1920
// #define SCREEN_H 4305
// #define SCREEN_W 5745

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
    else if(i.row() == 3 && i.column() == 0)
        toScreen(SC_SELECT);
    else if(i.row() == 3 && i.column() == 2)
        toScreen(SC_QUICK);
}

// Creates the main menu model to be used in the table.
QStandardItemModel *Main_Menu::createModel(){
    QStandardItemModel *model = new QStandardItemModel(4,3);
    QString str = QDir::currentPath();
    str += "/../Puzzling_Collections-master/Background.png";
    QImage *image = new QImage(str);
    int h = image->height()/4;
    int w = image->width()/3;
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 3; ++column) {
            QStandardItem *item = new QStandardItem();
            QImage part = image->copy(w*column, h*row, w, h);
            part = part.scaled(SCREEN_W/3, SCREEN_H/4);
            QBrush *brush = new QBrush(part);
            item->setBackground(*brush);
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
               table->setRowHeight(i, SCREEN_H/4);
           for(int i = 0; i < 3; i++)
               table->setColumnWidth(i, SCREEN_W/3);
           table->resize(SCREEN_W, SCREEN_H);

           QPalette palette = table->palette();
           QColor color(0,0,255,50);
           palette.setBrush(QPalette::Highlight,QBrush(color));
           palette.setBrush(QPalette::HighlightedText,QBrush(Qt::black));
           table->setPalette(palette);
           table->setFocusPolicy(Qt::NoFocus);
           table->setShowGrid(false);
           table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
           table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

           this->connect(table, SIGNAL(clicked(QModelIndex)), SLOT(onTableClicked(QModelIndex)));

           widget->setWindowTitle("Puzzling Collections");
           widget->resize(SCREEN_W, SCREEN_H);
           widget->setWindowState(Qt::WindowFullScreen);
           widget->show();
           INPUT ip;

           // Set up a generic keyboard event.
           ip.type = INPUT_KEYBOARD;
           ip.ki.wScan = 0; // hardware scan code for key
           ip.ki.time = 0;
           ip.ki.dwExtraInfo = 0;

           // Press the "A" key
           ip.ki.wVk = 0x91; // virtual-key code for the "a" key
           ip.ki.dwFlags = 0; // 0 for key press
           SendInput(1, &ip, sizeof(INPUT));

           // Release the "A" key
           ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
           SendInput(1, &ip, sizeof(INPUT));
}
