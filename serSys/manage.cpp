#include "manage.h"
#include "ui_manage.h"
#include"mainwindow.h"
manage::manage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::manage)
{
    ui->setupUi(this);
}

manage::~manage()
{
    delete ui;
}



void manage::on_push_saomiao_clicked()
{

}

void manage::on_push_firewallon_clicked()
{

}

void manage::on_push_firewalloff_clicked()
{

}
void MainWindow::manage(){

    QDialog *m = new QDialog();
    m->resize(500,700);
    m->setWindowTitle("软件管理");
    QLabel *xt = new QLabel(m);
    QPushButton *xtbtm = new QPushButton(m);
    xtbtm->setText("操作");
    xt->setText("系统检测");
    xt->setGeometry(50,100,100,50);
    xtbtm->setGeometry(200,100,50,50);

    QLabel *fireon = new QLabel(m);
    QPushButton *fireOnbtm = new QPushButton(m);
    fireOnbtm->setText("操作");
    fireon->setText("防火墙开启");
    fireon->setGeometry(50,200,100,50);
    fireOnbtm->setGeometry(200,200,50,50);

  //  int opt = 2;
    connect(fireOnbtm,SIGNAL(clicked()),this,SLOT(sendback2()));

    QLabel *fireoff = new QLabel(m);
    QPushButton *fireOffbtm = new QPushButton(m);
    fireOffbtm->setText("操作");
    fireoff->setText("防火墙关闭");
    fireoff->setGeometry(50,300,100,50);
    fireOffbtm->setGeometry(200,300,50,50);
//    opt = 3;
    connect(fireOffbtm,SIGNAL(clicked()),this,SLOT(sendback3()));


//opt = 1;
    connect(xtbtm,SIGNAL(clicked()),this,SLOT(sendback1()));
    m->show();
}
