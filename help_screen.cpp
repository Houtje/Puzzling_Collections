#include "help_screen.h"
#include "browse_screen.h"
#include "main_menu.h"
#include "puzzle.h"

#define ALL_IMAGES 5

// Constructor
Help_Screen::Help_Screen()
{
    table = NULL;
    widget = NULL;
}

// Destructor
Help_Screen::~Help_Screen(){

}

// Goes to one of the screens.
void Help_Screen::toScreen(Screen s){
    switch(s){
        case SC_MAIN: {
            Main_Menu *m = new Main_Menu();
            m->init();
            widget->close();
        } break;
        case SC_BROWSE: {
            Browse_Screen *b = new Browse_Screen(0);
            b->init();
            widget->close();
        } break;
        case SC_SELECT: {
            Puzzle *p = new Puzzle();
            p->init(0);
        } break;
        case SC_QUICK: {
            Puzzle *p = new Puzzle();
            srand(time(NULL));
            p->init(rand() % ALL_IMAGES);
        } break;
    }
}

// Starts several subprograms.
void Help_Screen::onTableClicked(const QModelIndex &i)
{
    if(i.row() == 0 && i.column() == 2)
        toScreen(SC_MAIN);
    else if(i.row() == 3 && i.column() == 0)
        toScreen(SC_BROWSE);
    else if(i.row() == 3 && i.column() == 1)
        toScreen(SC_SELECT);
    else if(i.row() == 3 && i.column() == 2)
        toScreen(SC_QUICK);
}

// Creates the help screen model to be used in the table.
QStandardItemModel *Help_Screen::createModel(){
    QStandardItemModel *model = new QStandardItemModel(4,3);
    QColor color(0,0,255,50);

    QStandardItem *item1 = new QStandardItem();
    QFont font1;
    font1.setPixelSize(50);
    item1->setFont(font1);
    item1->setTextAlignment(Qt::AlignCenter);
    item1->setData(QVariant(color), Qt::BackgroundRole);
    item1->setText("Browse");
    model->setItem(3, 0, item1);

    QStandardItem *item2 = item1->clone();
    item2->setText("Select and Play");
    model->setItem(3, 1, item2);

    QStandardItem *item3 = item1->clone();
    item3->setText("Quick Puzzle");
    model->setItem(3, 2, item3);

    QStandardItem *item4 = item1->clone();
    QFont font2;
    font2.setPixelSize(100);
    item4->setFont(font2);
    item4->setText("<-");
    model->setItem(0, 2, item4);

    QStandardItem *item5 = item1->clone();
    QFont font3;
    font3.setPixelSize(50);
    font3.setItalic(true);
    item5->setFont(font3);
    item5->setText("Puzzling Collections Help Screen");
    model->setItem(0, 1, item5);

    QStandardItem *item6 = item1->clone();
    QFont font4;
    font4.setPixelSize(20);
    item6->setFont(font4);
    item6->setText("Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor."
                   "Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus."
                   "Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem.");
    model->setItem(1, 1, item6);

    QStandardItem *item7 = item6->clone();
    item7->setText("Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. "
                   "In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. "
                   "Integer tincidunt. Cras dapibus.");
    model->setItem(2, 1, item7);

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


// Initializes the help screen.
void Help_Screen::init(){
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
