#include "test.h"
#include <QWidget>
#include <QTableView>
#include <QImage>
#include <QTextStream>
#include <QModelIndex>
#include <QMessageBox>
#include <iostream>
#include <sstream>
#include <string>

test::test()
{
    emp = {3,2};
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

void test::onTableClicked(const QModelIndex &i)
{
    if(i.row() == emp.row && i.column() == emp.column){
        // QStandardItem *item = new QStandardItem();
        // item->setData(QVariant(42));
        // i.model()->setItem(i.row(), i.column(), item);

        QMessageBox *box = new QMessageBox();
        box->setText(QString("wit"));
        box->show();
    }
}

void test::init()
{
    QWidget *widget = new QWidget();

    QStandardItemModel *model = new QStandardItemModel(4,3);
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 3; ++column) {
            if (row == 3 && column == 2) break;
            QString str = "C:/Users/Joris/Documents/Puzzling_Collections/images/_";
            str += ItoS(row);
            str += "_";
            str += ItoS(column);
            str += ".jpeg";
            QImage image(str);

            QStandardItem *item = new QStandardItem();
            item->setData(QVariant(QPixmap::fromImage(image)), Qt::DecorationRole);

            model->setItem(row, column, item);
        }
    }

    QTableView *table = new QTableView(widget);
    table->setModel(model);
    table->resizeColumnsToContents();
    table->resizeRowsToContents();
    table->resize(1920,1080);

    this->connect(table, SIGNAL(clicked(QModelIndex)), SLOT(onTableClicked(QModelIndex)));

    widget->setWindowTitle("Puzzling Collections");
    widget->resize(1920,1080);
    widget->show();
}
