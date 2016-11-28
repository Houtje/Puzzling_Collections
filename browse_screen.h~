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
<<<<<<< HEAD
#include <QDir>
=======
>>>>>>> 627d25b3ecb3405723aa84bfabecea8a320eeb19

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
<<<<<<< HEAD
    QImage *getFullImage(int number);
=======
    QImage getFullImage(int number);
>>>>>>> 627d25b3ecb3405723aa84bfabecea8a320eeb19

public slots:
    void onTableClicked(const QModelIndex &i);
};


#endif // BROWSE_SCREEN_H
