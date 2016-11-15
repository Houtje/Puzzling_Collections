#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QImage>
#include <QTextStream>
#include <iostream>
#include <sstream>
#include <string>

QString ItoS ( int number )
{
  std::ostringstream oss;
  oss << number;
  return QString::fromStdString(oss.str());
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget *widget = new QWidget();

    QStandardItemModel *model = new QStandardItemModel(4,3);
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 3; ++column) {
            QString str = "C:/Users/Joris/Documents/Puzzling_Collections/images/_";
            str += ItoS(row);
            str += "_";
            str += ItoS(column);
            str += ".jpeg";
            QImage image(str);
            QStandardItem *item = new QStandardItem();
            item->setData(QVariant(QPixmap::fromImage(image)), Qt::DecorationRole);
            //item->setSizeHint(QSize(100,100));
            model->setItem(row, column, item);
        }
    }

    QTableView *table = new QTableView(widget);
    table->setModel(model);
    table->resizeColumnsToContents();
    table->resizeRowsToContents();
    table->resize(1920,1080);

    widget->setWindowTitle("Puzzling Collections");
    widget->resize(1920,1080);
    widget->show();

    return a.exec();
}

