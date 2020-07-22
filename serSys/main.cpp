#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

   return a.exec();

}



//qmake -project ->pro.c
//qmake          ->makefile
//make
