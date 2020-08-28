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

//QTcpServer *server;
//QTcpSocket *clientConnection;

void MainWindow::socket()
{

    server = new QTcpServer(this);
 //   server->listen(QHostAddress::Any, 8888);//监听所有

 //   server->listen(QHostAddress::LocalHost, 8888);//监听所有QHostAddress::LocalHost

    if( server->listen(QHostAddress::Any,8888))connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
  //  qDebug()<<"是否链接姐姐"<<connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
   // connect(server, SIGNAL(newConnection()), this, SLOT(&MainWindow::acceptConnection));
   // acceptConnection();
}

void MainWindow::acceptConnection()
{
    qDebug()<<"sockeettttttttttttttt";
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
    QImage *img=new QImage; //新建一个image对象

    img->load(":/SuCai/gou.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
    QImage newimg = img->scaled(this->ui->gou1->width(),this->ui->gou1->height());
    this->ui->gou1->setPixmap(QPixmap::fromImage(newimg)); //
//    this->ui->gou1->setPicture(":/SuCai/logo.png");
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

void MainWindow::sendback1()
{
    //int opt = 1;
    //opt+=10;
    //qDebug()<<"sendback"<<(char *)opt;
   // QChar optchar = QChar(opt);
//    clientConnection->connectToHost("127.0.0.1", 9877);
//     clientConnection->waitForConnected();

    qDebug()<<"111111111111111111111";
    int opt = 1;
    QByteArray block;
    block.append(opt);
    clientConnection->write(block,sizeof(block));
//    clientConnection->write((char *)opt,sizeof((char *)opt));
    clientConnection->flush();
    clientConnection->waitForBytesWritten();
    qDebug("State:%d\n",clientConnection->state());  // State: 3（ConnectedState）正确
        //msleep(200);
   // clientConnection->flush();
}


void MainWindow::sendback2()
{
    qDebug()<<"2";
    int opt = 2;
    QByteArray block;
    block.append(opt);
    clientConnection->write(block,sizeof(block));
//    clientConnection->write((char *)opt,sizeof((char *)opt));
    clientConnection->flush();
    clientConnection->waitForBytesWritten();
    qDebug("State:%d\n",clientConnection->state());  // State: 3（ConnectedState）正确
        //msleep(200);
   // clientConnection->flush();
}


void MainWindow::sendback3()
{
    //int opt = 1;
    //opt+=10;
    //qDebug()<<"sendback"<<(char *)opt;
   // QChar optchar = QChar(opt);
     clientConnection = new QTcpSocket(this);
     clientConnection->connectToHost(info[1][0].ip, 8889);
     clientConnection->waitForConnected();

    qDebug()<<"33333333333333333";
    int opt = 3;
    QByteArray block;
    block.append(opt);
    clientConnection->write(block,sizeof(block));
//    clientConnection->write((char *)opt,sizeof((char *)opt));
    clientConnection->flush();
    clientConnection->waitForBytesWritten();
    qDebug("State:%d\n",clientConnection->state());  // State: 3（ConnectedState）正确
        //msleep(200);
   // clientConnection->flush();
}
