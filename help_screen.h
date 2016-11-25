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

class help_screen : public QObject
{
    Q_OBJECT
public slots:
    void onTableClicked(const QModelIndex &i);

public:
    help_screen();
    ~help_screen();
    void init();
    void startPuzzle();
    void returnToMain();
    QStandardItemModel *createModel();

private:
    QTableView *table;
    QWidget *widget;
};

#endif // HELP_SCREEN_H
