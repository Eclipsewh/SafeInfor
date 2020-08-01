#include<QtDebug>
#include  "socket.h"
#include <QTcpServer> //监听套接字
#include <QTcpSocket> //通信套接字//对方的(客户端的)套接字(通信套接字)
#include "widget.h"
#include <QProcess>
#include <string>
#include <QTextStream>

QTcpSocket *tcpClient;
QString message;  //存放从服务器接收到的字符串

void Widget::socket(){


    char data[] = "helllo!";
    tcpClient = new QTcpSocket(this);
    qDebug()<<"client---socket!";
   // tcpClient->connectToHost(QHostAddress("10.21.11.66"), 8888);
    tcpClient->connectToHost(QHostAddress("192.168.0.103"), 8888);
    //tcpClient->write(data);
    sendFile();
}

void Widget::sendFile(){
    QFile file("./info.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
  //  QString head = QString("%1").arg(file.fileName());
    QByteArray ba;// = head.toLatin1();
    char *point ;//= ba.data();
    char trans[2048];
    //strcpy(trans,point);
//    tcpClient->write(trans);
    QString line;
    do{
        qDebug()<<"xunhuan";
        line = in.readLine();
        //line;
        qDebug()<<line;
        ba=line.toLatin1();
        point = ba.data();
        char huanhang[] = "\n";
        strcpy(trans,point);
        strcat(trans,huanhang);
        tcpClient->write(trans);
    }while(!line.isNull());
    qDebug()<<"sendFile finished!";
}


/*
net user
netstat -a 查看开启了哪些端口,常用netstat -an
netstat -n 查看端口的网络连接情况，常用netstat -an
netstat -v 查看正在进行的工作

*/
