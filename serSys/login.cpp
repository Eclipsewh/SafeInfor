#include "login.h"
#include "ui_login.h"
#include<QString>
#include<QDebug>
#include<QMovie>
Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/SuCai/logo.png"));

    QMovie *iconShow = new QMovie(":/SuCai/bolang1.gif");
    //QMovie *iconShow = new QMovie(":/SuCai/back1.gif");
    //QMovie *iconShow = new QMovie(":/SuCai/mov1.gif");
    ui->label->resize(450,300);
    ui->label->setMovie(iconShow);
    iconShow->start();
}

Login::~Login()
{
    delete ui;
}

int Login::LoginIn()
{
    QString name = this->ui->name->text();
    QString password = this->ui->password->text();
    if(name=="33"&&password=="33"){
        return 1;
    }
    else{
        return 0;
    }

}

void Login::on_push_clicked()
{
    if(LoginIn()){
        qDebug()<<"login hide";
        this->hide();
      //  MainWindow w;
        w.setWindowTitle("WChecker");
        w.show();
    }
}

