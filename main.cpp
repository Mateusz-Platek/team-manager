#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    if (argc == 4) {
        w.createPerson(argv[1], argv[2], argv[3]);
    }
    w.show();
    return a.exec();
}
