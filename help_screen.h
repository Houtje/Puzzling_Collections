#ifndef HELP_SCREEN_H
#define HELP_SCREEN_H

#include <QObject>
#include <QTableView>
#include <QStandardItemModel>
#include <QWidget>
#include <QModelIndex>
#include <QFont>
#include <QColor>
#include <QPalette>
#include <time.h>
#include <cstdlib>

class Help_Screen : public QObject
{
    Q_OBJECT

protected:
    enum Screen {
        SC_QUICK,
        SC_SELECT,
        SC_MAIN,
        SC_BROWSE,
    };
    QTableView *table;
    QWidget *widget;

public:
    Help_Screen();
    ~Help_Screen();
    void init();
    void toScreen(Screen s);
    QStandardItemModel *createModel();

public slots:
    void onTableClicked(const QModelIndex &i);
};

#endif // HELP_SCREEN_H
