#include "puzzle.h"
#include "main_menu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    main_menu *m = new main_menu();

    m->init();

    return a.exec();
}
