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
    ui->setupUi(this);
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

