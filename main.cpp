#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>

#define WIDTH_DEF 400
#define LENGTH_DEF 300

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget *widget = new QWidget();

    QStandardItemModel *model = new QStandardItemModel(4,3);
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 3; ++column) {
            QStandardItem *item = new QStandardItem(QString("row %0, column %1").arg(row).arg(column));
            model->setItem(row, column, item);
        }
    }

    QTableView *table = new QTableView(widget);
    table->setFixedSize(WIDTH_DEF,LENGTH_DEF);
    table->setModel(model);

    widget->setWindowTitle("Puzzling Collections");
    table->setFixedSize(WIDTH_DEF,LENGTH_DEF);
    widget->show();

    return a.exec();
}

