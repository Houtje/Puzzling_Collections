#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QStandardItemModel>

class test : public QObject
{
    Q_OBJECT
public:
    struct empty{
        int row;
        int column;
    } emp;
    test();
    ~test();
    void init();

public slots:
    void onTableClicked(const QModelIndex &i);

};

#endif // TEST_H
