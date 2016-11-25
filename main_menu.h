#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <QObject>
#include <QTableView>
#include <QStandardItemModel>
#include <QWidget>
#include <QModelIndex>
#include <QFont>
#include <QColor>
#include <QPalette>

class main_menu : public QObject
{
    Q_OBJECT
public slots:
    void onTableClicked(const QModelIndex &i);

public:
    main_menu();
    ~main_menu();
    void init();
    void startPuzzle();
    void startHelp();
    QStandardItemModel *createModel();

private:
    QTableView *table;
    QWidget *widget;
};

#endif // MAIN_MENU_H
