<<<<<<< HEAD
#include "puzzle.h"
=======
#include "Puzzle.h"
>>>>>>> 627d25b3ecb3405723aa84bfabecea8a320eeb19

#define ALL_IMAGES 5

// Constructor
Puzzle::Puzzle()
{
    emp = {3,2};
    model = NULL;
    table = NULL;
    widget = NULL;
    imgNumber = 0;
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
<<<<<<< HEAD
QImage *Puzzle::getFullImage(int number){
    if(number >= 0 && number < ALL_IMAGES){
        QString str = QDir::currentPath();
        str += "/../Puzzling_Collections-master/images/";
        str += ItoS(number);
        str += ".jpg";
        QImage *image = new QImage(str);
        return image;
    }
    return NULL;
=======
QImage Puzzle::getFullImage(int number){
    if(number >= 0 && number < ALL_IMAGES){
        QString str = "C:/Users/Joris/Documents/Puzzling_Collections/images/";
        str += ItoS(number);
        str += ".jpg";
        QImage image(str);
        return image;
    }
    return QImage(NULL);
>>>>>>> 627d25b3ecb3405723aa84bfabecea8a320eeb19
}

// Gets the initial image for the tile specified.
QImage Puzzle::getImage(int row, int column, int number){
<<<<<<< HEAD
    QString str = QDir::currentPath();
    str += "/../Puzzling_Collections-master/images/";
=======
    QString str = "C:/Users/Joris/Documents/Puzzling_Collections/images/";
>>>>>>> 627d25b3ecb3405723aa84bfabecea8a320eeb19
    str += ItoS(number);
    str += "/_";
    str += ItoS(row);
    str += "_";
    str += ItoS(column);
    str += ".png";
    QImage image(str);
    return image;
}

// Shows the full picture after the puzzle is completed.
void Puzzle::onPuzzleCompleted(){
    QLabel *label = new QLabel();
<<<<<<< HEAD
    QImage image = *getFullImage(imgNumber);
=======
    QImage image = getFullImage(imgNumber);
>>>>>>> 627d25b3ecb3405723aa84bfabecea8a320eeb19
    label->setPixmap(QPixmap::fromImage(image));
    label->resize(1600,900);
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
    if((i.row() == emp.row-1 && i.column() == emp.column)
    ||(i.row() == emp.row && i.column() == emp.column-1)
    ||(i.row() == emp.row+1 && i.column() == emp.column)
    ||(i.row() == emp.row && i.column() == emp.column+1)){
        swapWithEmpty(i.row(), i.column());
        if(images == fullPicture){
            QMessageBox box;
            box.setText("Congratulations, you solved the puzzle!");
            box.exec();
            onPuzzleCompleted();
        }
    }
}

// Initializes the program with several values.
void Puzzle::init(int number)
{
    imgNumber = number;

    widget = new QWidget();

    model = new QStandardItemModel(4,3);
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 3; ++column) {
            QImage image = getImage(row, column, number);
            images.push_back(image);
            fullPicture.push_back(image);

            QStandardItem *item = new QStandardItem();
            item->setData(QVariant(QPixmap::fromImage(image)), Qt::DecorationRole);
            item->setSelectable(false);
            if (row == 3 && column == 2)
                item->setEnabled(false);
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
    table->resize(1625,915);

    this->connect(table, SIGNAL(clicked(QModelIndex)), SLOT(onTableClicked(QModelIndex)));

    widget->setWindowTitle("Puzzling Collections");
    widget->resize(1625,915);
    widget->show();
}
