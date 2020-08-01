#include "zhuce.h"
#include "ui_zhuce.h"
#include<QSqlQuery>
#include<QMessageBox>
#include<QDebug>
zhuce::zhuce(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::zhuce)
{
    ui->setupUi(this);
}

zhuce::~zhuce()
{
    delete ui;
}

void zhuce::on_pushButton_clicked()
{
    qDebug()<<"注册";
    QString name = this->ui->name->text();
    QString pzword = this->ui->pzword->text();
     QSqlQuery query;

     QString str = QString("insert into login(name, pzword) values('%1', '%2')").arg(name).arg(pzword);
            //QSqlQuery query;
    query.exec(str); //执行插入操作
    QMessageBox::information(NULL, "SUCCEED", "注册成功");
   this->close();
}
