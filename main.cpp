#include "puzzle.h"
#include "main_menu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Main_Menu *m = new Main_Menu();

    m->init();

    return a.exec();
}
