#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  "socket.h"
#include <QDebug>
#include <QString>
#include <QTableWidget>
#include <QTableWidgetItem>
//show 文件用来把安全信息显示到表格里
/*
typedef struct{
    QString pcname;
    QString ip;
    bool firewall;
    bool connected;
}INFO;
*/
QString bool2String(bool b);
void MainWindow::showInfo(int index)
{

    qDebug()<<"showinfo\n";

   this->ui->table->setItem(index,1,new QTableWidgetItem(info[index].pcname));
    this->ui->table->setItem(index,2,new QTableWidgetItem(info[index].ip));
    this->ui->table->setItem(index,3,new QTableWidgetItem(bool2String(info[index].firewall)));
    this->ui->table->setItem(index,4,new QTableWidgetItem(bool2String(info[index].connected)));
   this->ui->table->show();
    //info[index];

}

QString bool2String(bool b){
    if(b==true)return QString("Y");
    else return QString("N");
}


