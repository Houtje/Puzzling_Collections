#include "test.h"

QTextStream out(stdout);

test::test()
{
    emp = {3,2};
    model = NULL;
    table = NULL;
}

test::~test()
{

}

QString ItoS ( int number )
{
  std::ostringstream oss;
  oss << number;
  return QString::fromStdString(oss.str());
}

QImage getImage(int row, int column){
    QString str = "C:/Users/Joris/Documents/Puzzling_Collections/images/_";
    str += ItoS(row);
    str += "_";
    str += ItoS(column);
    str += ".png";
    QImage image(str);
    out << str << endl;
    return image;
}

void test::randomConfig(){
    srand(time(NULL));
    for(int i = 0; i < 30; i++){
        int move = rand() % 4;
        switch(move){
            case 0:
                if(emp.row+1 < 4)
                    swapWithEmpty(emp.row+1, emp.column);
                break;
            case 1:
                if(emp.row-1 > 0)
                    swapWithEmpty(emp.row-1, emp.column);
                break;
            case 2:
                if(emp.column+1 < 3)
                    swapWithEmpty(emp.row, emp.column+1);
                break;
            case 3:
                if(emp.column-1 > 0)
                    swapWithEmpty(emp.row, emp.column-1);
                break;
        }
    }
}

void test::swapWithEmpty(int row, int column){
    QImage image = images[(row*3 + column)];
    QStandardItem *item = new QStandardItem();
    QStandardItem *emp_item = new QStandardItem();

    item->setData(QVariant(QPixmap::fromImage(images[(row*3 + column)])), Qt::DecorationRole);
    emp_item->setData(QVariant(QPixmap::fromImage(images[(emp.row*3 + emp.column)])), Qt::DecorationRole);

    model->setItem(emp.row, emp.column, item);
    model->setItem(row, column, emp_item);

    images[(row*3 + column)] = images[(emp.row*3 + emp.column)];
    images[(emp.row*3 + emp.column)] = image;

    emp.row = row;
    emp.column = column;
}

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
        }
    }
}

void test::init()
{
    QWidget *widget = new QWidget();

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
