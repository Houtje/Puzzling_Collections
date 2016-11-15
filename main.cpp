#include "test.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    test *t = new test();

    t->init();

    return a.exec();
}
