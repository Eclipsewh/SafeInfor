#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  "socket.h"
#include <QTcpServer> //监听套接字
#include <QTcpSocket> //通信套接字//对方的(客户端的)套接字(通信套接字)
#include<QDebug>
#include <QTextStream>

//void acceptConnection();
//void readClient();

QTcpServer *server;
QTcpSocket *clientConnection;

void MainWindow::socket()
{
    server = new QTcpServer(this);
    server->listen(QHostAddress::Any, 8888);//监听所有

    connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
   // acceptConnection();
}

void MainWindow::acceptConnection()
{
    clientConnection = server->nextPendingConnection();
    connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readClient()));
}


void MainWindow::readClient()
{
    qDebug()<<"read client";
    QString str;
   //qDebug()<<str;

    int pos = num_of_pc + 1;
 //   str = clientConnection->readALL();
    str = clientConnection->readLine();
    info[pos].pcname = str;
qDebug()<<str;
   str = clientConnection->readLine();
//str = clientConnection->readAll();
    info[pos].ip = str;
qDebug()<<str;

 str = clientConnection->readLine();
  //  str = clientConnection->readAll();
    info[pos].firewall = str=="true"?true:false;
    qDebug()<<str;
 str = clientConnection->readLine();
  //  str = clientConnection->readAll();
    info[pos].connected = str=="true"?true:false;

    //或者
    //char buf[1024];
    //clientConnection->read(buf,1024);
    //qDebug()<<buf;
    qDebug()<<str;
    ++num_of_pc;
}


void MainWindow::evaluate()
{
}

void MainWindow::feedback()
{
}
