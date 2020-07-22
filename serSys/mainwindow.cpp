#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  "socket.h"
#include <QDebug>

//mainwindow 负责一个主要功能的展示，对应pptNo2

//主界面
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
    qDebug()<<"showinfo  mainwindow\n";
    this->ui->table = new QTableWidget(5,6,this->ui->table);
    this->ui->table->resize(50000,5000);
   QStringList headers;
   headers << "主机名" << "IP" << "联网" << "防火墙";
   this->ui->table->setHorizontalHeaderLabels(headers);
   this->ui->table->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ask1_clicked()
{
    qDebug()<<("socket");
    socket();  //开始通信


}

void MainWindow::on_evaluate1_clicked()
{
    evaluate();//评估开始
}

void MainWindow::on_feedback2_clicked()
{
    feedback();//反馈
}

