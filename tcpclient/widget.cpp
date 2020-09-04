#include "widget.h"
#include "ui_widget.h"
#include<QMovie>
#include"firethread2.h"
#include"filethread.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->HostIP->setPlaceholderText("请输入主机IP地址");
    QMovie *iconShow = new QMovie(":/SuCai/quan2.gif");
    ui->label->setMovie(iconShow);
    iconShow->start();

}

void Widget::startThread(){
   fileThread *workerThread = new fileThread(curAddress);
   workerThread->start();
}

void Widget::startThread2(){
   fireThread2 *workerThread = new fireThread2(curAddress);
   workerThread->start();
}


Widget::~Widget()
{
    delete ui;
}

void Widget::on_send_clicked()
{
    socket();
}

void Widget::on_search_clicked()
{
    search();
}

void Widget::on_manage_clicked()
{

//    QByteArray block;
//    int area=1;
////    tcpClient->read(area);
//    qDebug()<<"manage"<<area;
    _socket();

}
