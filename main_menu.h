#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <QObject>
#include <QTableView>
#include <QStandardItemModel>
#include <QWidget>
#include <QModelIndex>
#include <QFont>
#include <QKeyEvent>
#include <QEvent>
#include <QColor>
#include <QPalette>
#include <time.h>
#include <cstdlib>

class Main_Menu : public QObject
{
    Q_OBJECT

protected:
    enum Screen {
        SC_QUICK,
        SC_SELECT,
        SC_HELP,
        SC_BROWSE,
    };
    QTableView *table;
    QWidget *widget;

public:
    Main_Menu();
    ~Main_Menu();
    void init();
    void toScreen(Screen s);
    QStandardItemModel *createModel();

public slots:
    void onTableClicked(const QModelIndex &i);
};



#endif // MAIN_MENU_H
