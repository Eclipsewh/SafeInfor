#include "mainwindow.h"
#include"login.h"
#include <QApplication>
#include<QTimer>
#include<QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login log;
    log.setWindowTitle("WChecker");
    log.resize(600,800);
    log.show();
//    MainWindow w;
//    w.hide();
//    w.setWindowTitle("WChecker");
    //w.setWindowOpacity(0.5);
//    qDebug()<<"is hidden"<<log.isHidden();
//    if(log.isHidden()){
//        qDebug()<<"is hidden";
//        w.show();
//    }
    return a.exec();


}



//qmake -project ->pro.c
//qmake          ->makefile
//make
