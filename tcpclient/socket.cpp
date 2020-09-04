#include<QtDebug>
#include  "socket.h"
#include <QTcpServer> //监听套接字
#include <QTcpSocket> //通信套接字//对方的(客户端的)套接字(通信套接字)
#include "widget.h"
#include <QProcess>
#include <string>
#include <QTextStream>
#include"widget.h"
#include "ui_widget.h"
//QTcpSocket *tcpClient;
QString message;  //存放从服务器接收到的字符串

void Widget::socket(){

    char data[] = "helllo!";
    tcpClient = new QTcpSocket(this);
    qDebug()<<"client---socket!";
   tcpClient->connectToHost(QHostAddress("192.168.56.1"), 8888);
   // QString ip = this->ui->HostIP->text();

    //tcpClient->connectToHost(QHostAddress(ip), 8888);

    //tcpClient->write(data);
    send();
}

void Widget::send(){
    sendFile("./info.txt");
    sendFile("./info2.txt");
    sendFile("./info1.txt");
}


void Widget::sendFile(QString fileName){
//    QFile file("./info.txt");
    qDebug()<<"send file "<<fileName;
    QFile file(fileName);
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

void Widget::acceptConnection()
{
    qDebug()<<"sockeettttttttttttttt";
//     QTcpSocket *clientConnection;
    clientConnection = server->nextPendingConnection();
    connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readClient()));
}



void Widget::_socket()
{
    qDebug()<<"_socket";
    //QTcpServer *server = new QTcpServer(this);
    server = new QTcpServer(this);
    if( server->listen(QHostAddress::Any,8889))connect(server, SIGNAL(newConnection()), this, SLOT(accept()));
}

void Widget::accept(){
    qDebug()<<"sockeettttttttttttttt";
//     QTcpSocket *clientConnection;
    clientConnection = server->nextPendingConnection();
    connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readClient()));
}


void Widget::readClient()
{
    qDebug()<<"read client22";
    QString str;


    str = clientConnection->readLine();//pcname
    if(str.isNull()||str.isEmpty()){
        qDebug()<<"空";
        return;
    }
    qDebug()<<"   "<<str[0].toLatin1();
    manage(str[0].toLatin1());

}



/*
net user
netstat -a 查看开启了哪些端口,常用netstat -an
netstat -n 查看端口的网络连接情况，常用netstat -an
netstat -v 查看正在进行的工作

*/
