#ifndef PUZZLE_H
#define PUZZLE_H

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

class Puzzle : public QObject
{
    Q_OBJECT

protected:
    struct empty{
        int row;
        int column;
    } emp;
    QStandardItemModel *model;
    QTableView *table;
    QWidget *widget;
    std::vector<QImage> images;
    std::vector<QImage> fullPicture;
    int imgNumber;

public:
    Puzzle();
    ~Puzzle();
    void init(int number);
    void swapWithEmpty(int row, int column);
    void randomConfig();
    void onPuzzleCompleted();
    void disableSelection();
    QImage getImage(int row, int column, int number);
    QImage getFullImage(int number);
    QString ItoS(int number);

public slots:
    void onTableClicked(const QModelIndex &i);
};

#endif // PUZZLE_H
