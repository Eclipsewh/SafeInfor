#include "widget.h"
#include "ui_widget.h"
#include<QMovie>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QMovie *iconShow = new QMovie(":/SuCai/quan2.gif");
    ui->label->setMovie(iconShow);
    iconShow->start();

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
