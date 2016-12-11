#ifndef SELECT_AND_PLAY_H
#define SELECT_AND_PLAY_H

#include <QObject>
#include <QTableView>
#include <QStandardItemModel>
#include <QCoreApplication>
#include <QWidget>
#include <QModelIndex>
#include <QFont>
#include <QColor>
#include <QPalette>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QDir>


class Select_And_Play : public QObject
{
    Q_OBJECT

protected:
    enum Screen {
        SC_MAIN,
        SC_DIFF,
    };
    QTableView *table;
    QWidget *widget;
    int imgBlock;
    int clickedImage;

public:
    Select_And_Play(int block);
    ~Select_And_Play();
    void init();
    void toScreen(Screen s);
    QStandardItemModel *createModel();
    QString ItoS(int number);
    QImage *getFullImage(int number);

public slots:
    void onTableClicked(const QModelIndex &i);
};

#endif // SELECT_AND_PLAY_H
