#ifndef DIFFICULTY_SCREEN_H
#define DIFFICULTY_SCREEN_H

#include <QObject>
#include <QTableView>
#include <QStandardItemModel>
#include <QWidget>
#include <QModelIndex>
#include <QFont>
#include <QColor>
#include <QPalette>

class Difficulty_Screen : public QObject
{
    Q_OBJECT

protected:
    enum Screen {
        SC_BROWSE,
        SC_PUZZLE,
    };
    QTableView *table;
    QWidget *widget;
    int clickedImage;

public:
    Difficulty_Screen(int image);
    ~Difficulty_Screen();
    void init();
    void toScreen(Screen s);
    QStandardItemModel *createModel();
    QString ItoS(int number);
    QImage *getFullImage(int number);

public slots:
    void onTableClicked(const QModelIndex &i);
};

#endif // DIFFICULTY_SCREEN_H
