#ifndef BROWSE_SCREEN_H
#define BROWSE_SCREEN_H

#include <QObject>
#include <QTableView>
#include <QStandardItemModel>
#include <QWidget>
#include <QModelIndex>
#include <QFont>
#include <QColor>
#include <QPalette>
#include <QDialogButtonBox>
#include <QPushButton>

#include <QDir>


class Browse_Screen : public QObject
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
    Browse_Screen(int block);
    ~Browse_Screen();
    void init();
    void toScreen(Screen s);
    QStandardItemModel *createModel();
    QString ItoS(int number);

    QImage *getFullImage(int number);

public slots:
    void onTableClicked(const QModelIndex &i);
};


#endif // BROWSE_SCREEN_H
