#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QStandardItemModel>
#include <QTableView>
#include <QWidget>
#include <QImage>
#include <QPicture>
#include <QLabel>
#include <QTextStream>
#include <QModelIndex>
#include <QMessageBox>
#include <QHeaderView>
#include <QEvent>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <time.h>

class test : public QObject
{
    Q_OBJECT
public:
    struct empty{
        int row;
        int column;
    } emp;

    test();
    ~test();
    void init();
    void swapWithEmpty(int row, int column);
    void randomConfig();
    void onPuzzleCompleted();

    QStandardItemModel *model;
    QTableView *table;
    QWidget *widget;
    std::vector<QImage> images;
    std::vector<QImage> fullPicture;

public slots:
    void onTableClicked(const QModelIndex &i);

};

#endif // TEST_H
