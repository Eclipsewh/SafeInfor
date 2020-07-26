#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  "socket.h"
#include <QTcpServer> //监听套接字
#include <QTcpSocket> //通信套接字//对方的(客户端的)套接字(通信套接字)
#include<QDebug>
#include <QTextStream>
#include<QTime>

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


    str = clientConnection->readLine();//pcname
    if(str.isNull()||str.isEmpty()){
        qDebug()<<"空";
        return;
    }
    int pos = findPos(str);
    qDebug()<<"pos"<<pos;
    INFO *cur=NULL;
    if(pos==-1){
        pos = num_of_pc + 1;
         ++num_of_pc;qDebug()<<"pos1 "<<pos;
        INFO newNode;
        info[pos].append(newNode);
        info[pos].append(newNode);
        cur = &info[num_of_pc][1];
        cur->cnt = 1;
    }else{
        INFO newNode;
        info[pos].append(newNode);
        qDebug()<<"pos2"<<pos;
        //info[pos].next = (INFO *)malloc(sizeof(INFO));
        cur = &info[pos][++info[pos][1].cnt];
    }
    qDebug()<<"here";
    cur ->score = 60;
    cur->time = getTime();
    cur->index = pos;
    cur->pcname = str;
    qDebug()<<str;
    str = clientConnection->readLine();

    cur->ip = str;
    qDebug()<<str;

    str = clientConnection->readLine();

    cur->firewall = str=="true"?true:false;
    qDebug()<<str;
    str = clientConnection->readLine();
  //  str = clientConnection->readAll();
    cur->connected = str=="true"?true:false;

    //或者
    //char buf[1024];
    //clientConnection->read(buf,1024);
    //qDebug()<<buf;
    qDebug()<<str;

    showInfo(cur);
/*
    info[pos].pcname = str;
    qDebug()<<str;
    str = clientConnection->readLine();

    info[pos].ip = str;
    qDebug()<<str;

    str = clientConnection->readLine();

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

    showInfo(pos);
    */
}

QString MainWindow::getTime(){
    QDateTime current_time = QDateTime::currentDateTime();
    //QTime current_time = QTime::currentTime();
//    int hour = current_time.hour();        //当前的小时
//    int min = current_time.minute();    //当前的分
//    int sec = current_time.second();    //当前的秒
//    QString time = QString::number(hour) + "h/" +QString::number(min) + "m/"+QString::number(sec)+"s" ;
     QString time = current_time.toString("yyyy/MM/dd/hh/mm/ss/ddd");
    return time;
}


void MainWindow::evaluate()
{
}

void MainWindow::feedback()
{
}
