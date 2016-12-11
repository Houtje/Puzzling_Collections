#include "puzzle.h"

#define ALL_IMAGES 11
#define SCREEN_H 900
#define SCREEN_W 1600

// Constructor
Puzzle::Puzzle()
{
    emp = {3,2};
    model = NULL;
    table = NULL;
    widget = NULL;
    imgNumber = 0;
    hardMode = false;
    for(int i = 0; i < 10; i++)
        solved[i] = false;
}

// Destructor
Puzzle::~Puzzle()
{

}

// Converts an integer to a string.
QString Puzzle::ItoS(int number)
{
  std::ostringstream oss;
  oss << number;
  return QString::fromStdString(oss.str());
}

// Gets the full image at the number specified.
QImage *Puzzle::getFullImage(int number){
    if(number >= 0 && number < ALL_IMAGES){
        QString str = QDir::currentPath() + "/../Naturalis/";
        str += ItoS(number);
        str += ".png";
        QImage *image = new QImage(str);
        return image;
    }
    return NULL;
}

// Shows the full picture after the puzzle is completed.
void Puzzle::onPuzzleCompleted(){
    QMessageBox box;
    box.setText("Congratulations, you solved the puzzle!");
    box.exec();
    QLabel *label = new QLabel();
    QImage image = *getFullImage(imgNumber);
    image = image.scaled(SCREEN_W, SCREEN_H);
    label->setPixmap(QPixmap::fromImage(image));
    label->resize(SCREEN_W, SCREEN_H);
    label->show();
    widget->close();
}

// Loops turns to create a random starting configuration.
void Puzzle::randomConfig(){
    srand(time(NULL));
    for(int i = 0; i < 100; i++){
        int move = rand() % 4;
        switch(move){
            case 0:
                if(emp.row+1 < 4)
                    swapWithEmpty(emp.row+1, emp.column);
                break;
            case 1:
                if(emp.row-1 >= 0)
                    swapWithEmpty(emp.row-1, emp.column);
                break;
            case 2:
                if(emp.column+1 < 3)
                    swapWithEmpty(emp.row, emp.column+1);
                break;
            case 3:
                if(emp.column-1 >= 0)
                    swapWithEmpty(emp.row, emp.column-1);
                break;
        }
    }
}

// Disables selection for all elements.
void Puzzle::disableSelection(){
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 3; ++c)
            model->item(r,c)->setSelectable(false);
}

// Swaps the tile specified with the empty tile.
void Puzzle::swapWithEmpty(int row, int column){
    QStandardItem *item = new QStandardItem();
    QStandardItem *emp_item = new QStandardItem();

    item->setData(QVariant(QPixmap::fromImage(images[(row*3 + column)])), Qt::DecorationRole);
    emp_item->setData(QVariant(QPixmap::fromImage(images[(emp.row*3 + emp.column)])), Qt::DecorationRole);

    emp_item->setEnabled(false);
    item->setEnabled(true);

    model->setItem(emp.row, emp.column, item);
    model->setItem(row, column, emp_item);

    QImage image = images[(row*3 + column)];
    images[(row*3 + column)] = images[(emp.row*3 + emp.column)];
    images[(emp.row*3 + emp.column)] = image;

    emp.row = row;
    emp.column = column;

    disableSelection();
}

// Swaps the tile if applicable.
void Puzzle::onTableClicked(const QModelIndex &i)
{
    if(!(i.row() == emp.row && i.column() == emp.column)
    && !solved[i.row()*3 + i.column()] && hardMode){
        Puzzle *p = new Puzzle();
        p->initNM(imgNumber, new QImage(images[i.row()*3 + i.column()]));
    }
    else{
        if((i.row() == emp.row-1 && i.column() == emp.column)
        ||(i.row() == emp.row && i.column() == emp.column-1)
        ||(i.row() == emp.row+1 && i.column() == emp.column)
        ||(i.row() == emp.row && i.column() == emp.column+1)){
            swapWithEmpty(i.row(), i.column());
            if(images == fullPicture)
                onPuzzleCompleted();
        }
    }
}

// Initializes the normal mode with several values.
void Puzzle::initNM(int number, QImage *subPuzzle)
{
    imgNumber = number;

    widget = new QWidget();

    model = new QStandardItemModel(4,3);
    QImage *img = getFullImage(number);
    int h = img->height()/4;
    int w = img->width()/3;
    if(subPuzzle){
        QImage newImg = subPuzzle->scaled(SCREEN_W, SCREEN_H);;
        *img = newImg;
    }
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 3; ++column) {
            QStandardItem *item = new QStandardItem();

            QImage part = img->copy(w*column, h*row, w, h);
            part = part.scaled(SCREEN_W/3, SCREEN_H/4);
            if(row == 3 && column == 2){
                part.fill(QColor(255,255,255));
                item->setEnabled(false);
            }
            images.push_back(part);
            fullPicture.push_back(part);

            item->setData(QVariant(QPixmap::fromImage(part)), Qt::DecorationRole);
            item->setSelectable(false);
            model->setItem(row, column, item);
        }
    }

    randomConfig();

    table = new QTableView(widget);
    table->setModel(model);
    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();
    table->resizeColumnsToContents();
    table->resizeRowsToContents();
    table->resize(SCREEN_W+25, SCREEN_H+15);

    this->connect(table, SIGNAL(clicked(QModelIndex)), SLOT(onTableClicked(QModelIndex)));

    widget->setWindowTitle("Puzzling Collections");
    widget->resize(SCREEN_W+25, SCREEN_H+15);
    widget->show();
}

// Initializes the hard mode with several values.
void Puzzle::initHM(int number)
{
    imgNumber = number;

    hardMode = true;

    widget = new QWidget();

    model = new QStandardItemModel(4,3);
    QImage *img = getFullImage(number);
    int h = img->height()/4;
    int w = img->width()/3;
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 3; ++column) {
            QStandardItem *item = new QStandardItem();

            QImage part = img->copy(w*column, h*row, w, h);
            if(row == 3 && column == 2){
                part.fill(QColor(255,255,255));
                item->setEnabled(false);
            }
            images.push_back(part);
            fullPicture.push_back(part);

            item->setData(QVariant(QPixmap::fromImage(part)), Qt::DecorationRole);
            item->setSelectable(false);
            model->setItem(row, column, item);
        }
    }

    randomConfig();

    table = new QTableView(widget);
    table->setModel(model);
    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();
    table->resizeColumnsToContents();
    table->resizeRowsToContents();
    table->resize(SCREEN_W+25, SCREEN_H+15);

    this->connect(table, SIGNAL(clicked(QModelIndex)), SLOT(onTableClicked(QModelIndex)));

    widget->setWindowTitle("Puzzling Collections");
    widget->resize(SCREEN_W+25, SCREEN_H+15);
    widget->show();
}
