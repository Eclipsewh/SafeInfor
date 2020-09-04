#include "widget.h"
#include<QIcon>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    w.setWindowTitle("WChecker");
   // setWindowIcon(QIcon(":/SuCai/logo.png"));
    w.setWindowIcon(QIcon(":/SuCai/logo.png"));
    w.show();
    return a.exec();
}


//QTcpSocket *tcpSocket;
//QString message;  //存放从服务器接收到的字符串
