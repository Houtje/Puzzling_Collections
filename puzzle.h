#ifndef puzzle_H
#define puzzle_H

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
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <time.h>

class puzzle : public QObject
{
    Q_OBJECT
public:
    struct empty{
        int row;
        int column;
    } emp;

    puzzle();
    ~puzzle();
    void init();
    void swapWithEmpty(int row, int column);
    void randomConfig();
    void onPuzzleCompleted();
    void disableSelection();

private:
    QStandardItemModel *model;
    QTableView *table;
    QWidget *widget;
    std::vector<QImage> images;
    std::vector<QImage> fullPicture;

public slots:
    void onTableClicked(const QModelIndex &i);

};

#endif // puzzle_H
