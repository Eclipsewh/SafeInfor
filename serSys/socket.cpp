#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  "socket.h"
#include <QTcpServer> //监听套接字
#include <QTcpSocket> //通信套接字//对方的(客户端的)套接字(通信套接字)
#include<QDebug>
#include <QTextStream>
#include<QTime>
#include"info.h"
#include<QList>
//void acceptConnection();
//void readClient();

//QTcpServer *server;
//QTcpSocket *clientConnection;

void MainWindow::socket(int port,int index)
{
   // --index;
    pcIndex = index;
    server = new QTcpServer(this);
 //   server->listen(QHostAddress::Any, 8888);//监听所有

 //   server->listen(QHostAddress::LocalHost, 8888);//监听所有QHostAddress::LocalHost

    if( server->listen(QHostAddress::Any,port))connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
  //  qDebug()<<"是否链接姐姐"<<connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
   // connect(server, SIGNAL(newConnection()), this, SLOT(&MainWindow::acceptConnection));
   // acceptConnection();
    QList<QTcpSocket*> *socket_list = new QList<QTcpSocket*>;
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
    int index = pcIndex;
    int pos = findPos(str);
    qDebug()<<"pos"<<pos;
    INFO *cur=NULL;
    if(pos==-1){//新的主机
        pos = num_of_pc + 1;
        pos = index;
         ++num_of_pc;qDebug()<<"pos1 "<<pos;
        INFO newNode;
        info[pos].append(newNode);
        info[pos].append(newNode);
        cur = &info[num_of_pc][1];
        cur->cnt = 1;
    }else{
        pos = index;
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

    //端口数
    qDebug()<<str;
    str = clientConnection->readLine();
    cur->portNum = str.toInt();
    //端口

    for(int i=0;i<cur->portNum;++i){
        str = clientConnection->readLine();
        QStringList list = str.split(' ');
        duankou newPort;
        qDebug()<<"str"<<str<<"port"<<list[0]<<"ser"<<list[list.size()-1];
        newPort.port_num = list[0];
        newPort.service = list[list.size()-1];
        cur->port.append(newPort);
    }

    str = clientConnection->readLine();
    cur->type = str;
    str = clientConnection->readLine();
    cur->physical = str;
    str = clientConnection->readLine();
    cur->vir = str;

    int final_score = 100;
    if(!cur->firewall)final_score-=20;
    if(cur->connected)final_score-=3;
    final_score-=cur->cveNum*10;
    cur->score = final_score;


    //info1内容，cve数量和cve
    str = clientConnection->readLine();
    cur->cveNum = str.toInt();
    for(int i=0;i<cur->cveNum;++i){
        str = clientConnection->readLine();
        cur->CVE.append(str);
    }



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

    qDebug()<<"111111111111111111111";

    send = new QTcpSocket(this);
    send->connectToHost(info[manIndex][1].ip, 8889);
    send->waitForConnected();

    int opt = 4;
    QByteArray block;
    block.append(opt);
    send->write(block,sizeof(block));
    send->flush();
    send->waitForBytesWritten();
    qDebug("State:%d\n",send->state());  // State: 3（ConnectedState）正确
        //msleep(200);
   // clientConnection->flush();
 //   send->close();
}


void MainWindow::sendback2()
{
    qDebug()<<"2";
    send = new QTcpSocket(this);
    send->connectToHost(info[manIndex][1].ip, 8889);
    send->waitForConnected();

   qDebug()<<info[manIndex][1].ip;
    int opt = 2;
    QByteArray block;
    block.append(opt);
    send->write(block,sizeof(block));
//    clientConnection->write((char *)opt,sizeof((char *)opt));
   send->flush();
    send->waitForBytesWritten();
    qDebug("State:%d\n",send->state());  // State: 3（ConnectedState）正确
        //msleep(200);
   // clientConnection->flush();
  //  send->close();
}


void MainWindow::sendback3()
{
    //int opt = 1;
    //opt+=10;
    //qDebug()<<"sendback"<<(char *)opt;
   // QChar optchar = QChar(opt);
     send = new QTcpSocket(this);
     send->connectToHost(info[manIndex][1].ip, 8889);
     send->waitForConnected();
    qDebug()<<"33333333333333333";
    int opt = 3;
    QByteArray block;
    block.append(opt);
    send->write(block,sizeof(block));
//    clientConnection->write((char *)opt,sizeof((char *)opt));
    send->flush();
    send->waitForBytesWritten();
    qDebug("State:%d\n",send->state());  // State: 3（ConnectedState）正确
        //msleep(200);
   // clientConnection->flush();
    //send->close();
}
