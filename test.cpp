#include "test.h"

QTextStream out(stdout);

// Constructor
test::test()
{
    emp = {3,2};
    model = NULL;
    table = NULL;
    widget = NULL;
}

// Destructor
test::~test()
{

}

// Converts an integer to a string.
QString ItoS ( int number )
{
  std::ostringstream oss;
  oss << number;
  return QString::fromStdString(oss.str());
}

// Gets the initial image for the tile specified.
QImage getImage(int row, int column){
    QString str = "C:/Users/Joris/Documents/Puzzling_Collections/images/_";
    str += ItoS(row);
    str += "_";
    str += ItoS(column);
    str += ".png";
    QImage image(str);
    return image;
}

// WIP: Shows the full picture after the puzzle is completed.
void test::onPuzzleCompleted(){
    QLabel *label = new QLabel();
    label->setPixmap(QPixmap("C:/Users/Joris/Documents/Puzzling_Collections/images/full.png"));
    label->resize(1625,915);
    label->show();
    label->setVisible(true);
    label->setFocus();
    widget->close();
}

// Loops turns to create a random starting configuration.
void test::randomConfig(){
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

// Swaps the tile specified with the empty tile.
void test::swapWithEmpty(int row, int column){
    QStandardItem *item = new QStandardItem();
    QStandardItem *emp_item = new QStandardItem();

    item->setData(QVariant(QPixmap::fromImage(images[(row*3 + column)])), Qt::DecorationRole);
    emp_item->setData(QVariant(QPixmap::fromImage(images[(emp.row*3 + emp.column)])), Qt::DecorationRole);

    model->setItem(emp.row, emp.column, item);
    model->setItem(row, column, emp_item);

    QImage image = images[(row*3 + column)];
    images[(row*3 + column)] = images[(emp.row*3 + emp.column)];
    images[(emp.row*3 + emp.column)] = image;

    emp.row = row;
    emp.column = column;
}

// Swaps the tile if applicable.
void test::onTableClicked(const QModelIndex &i)
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
void test::init()
{
    widget = new QWidget();

    model = new QStandardItemModel(4,3);
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 3; ++column) {
            QImage image = getImage(row, column);
            images.push_back(image);
            fullPicture.push_back(image);

            QStandardItem *item = new QStandardItem();
            item->setData(QVariant(QPixmap::fromImage(image)), Qt::DecorationRole);

            model->setItem(row, column, item);
        }
    }

    // randomConfig();

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
