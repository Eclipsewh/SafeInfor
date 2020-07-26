#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  "socket.h"
#include"show.h"
#include <QDebug>
#include<QSplineSeries>
#include<QButtonGroup>
#include <QChartView>
#include <QChart>
#include<QValueAxis>
#include <QHBoxLayout>
#include<QtWidgets>
QT_CHARTS_USE_NAMESPACE
//mainwindow 负责一个主要功能的展示，对应pptNo2

//主界面
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowIcon(QIcon(":/SuCai/logo.png"));
    setWindowTitle("SafeManager");
   // setWindowIconText("安全管理系统");
    //setWindowOpacity();
    this->ui->setupUi(this);
    qDebug()<<"showinfo  mainwindow\n";


    QMovie *iconShow = new QMovie(":/SuCai/mov1.gif");
    ui->label0->setMovie(iconShow);
    iconShow->start();
    num_of_pc = 0;
    this->ui->table = new QTableWidget(5,6,this->ui->table);
    this->ui->table->resize(50000,5000);
   QStringList headers;
   headers << "主机名" << "IP" << "联网" << "防火墙"<<"获取时间"<<"分数";
   this->ui->table->setHorizontalHeaderLabels(headers);
   this->ui->table->show();
   //this->ui->backLabel9->setFrameShape(QtWidgets.QFrame.Box);
   //this->ui->backLabel9->setFrameShadow(QtWidgets.QFrame.Raised);

//   this->ui->backLabel9->setLineWidth(5);

//   //this->ui->backLabel9->setStyleSheet("border:rgb(170,255,255)");
//   this->ui->backLabel9->setStyleSheet("border-color:black");
   //this->ui->backLabel9->setStyleSheet("background-color:rgb(170,255,255)");

   qDebug()<<"page 1";
   //drawPic(&info[1][1]);
   qDebug()<<"page 1 finish";
 //  QMainWindow w;

       QChart *chart = new QChart();
       chart->legend()->hide();
       chart->setTitle("安全线曲线图");
      // chart->createDefaultAxes();
       QSplineSeries *series = new QSplineSeries();//曲线图
       series->setVisible(true);
       series->append(1,0);

       chart->addSeries(series);
       chart->createDefaultAxes();
        chart->legend()->setVisible(true);//设置是否可视
       // axisX = new QValueAxis;
        chart->axisY()->setRange(0,100);
         chart->axisX()->setRange(1,32);
      // chart->setAxisX(axis, series);
    //  chart->setGeometry(790,50,480,400);
     // chart->resize(480,400);
      this->ui->widget1->setChart(chart);
      this->ui->widget1->resize(700, 420);
      this->ui->widget1->show();


//         QPushButton *year = new QPushButton(this->ui);
//         QPushButton *month = new QPushButton(this);
//         QPushButton *week = new QPushButton(this);
//         QPushButton *day = new QPushButton(this);
//         year->setText(QString("年"));
//         month->setText(QString("月"));
//         week->setText(QString("周"));
//         day->setText(QString("日"));
//     //    year->setFixedSize(30,45);
//     //    month->setFixedSize(30,45);
//     //    day->setFixedSize(30,45);

//         year->setGeometry(1300,400,50,26);
//         month->setGeometry(1370,400,50,26);
//         week->setGeometry(1300,470,50,26);
//         day->setGeometry(1370,470,50,26);
//     //    year->setVisible(true);
//     //    month->setVisible(true);
//     //    day->setVisible(true);
//     //    week->setVisible(true);

//         year->show();
//         month->show();
//         week->show();
//         day->show();
         QButtonGroup * buttonGroup = new QButtonGroup(this);
        buttonGroup->addButton(this->ui->selectA);
        buttonGroup->addButton(this->ui->selectB);
        buttonGroup->addButton(this->ui->selectC);
         buttonGroup->setExclusive(true);
         QButtonGroup * buttonGroup2 = new QButtonGroup(this);
        buttonGroup2->addButton(this->ui->year);
        buttonGroup2->addButton(this->ui->month);
        buttonGroup2->addButton(this->ui->day);
        buttonGroup2->addButton(this->ui->week);
         buttonGroup2->setExclusive(true);


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


void MainWindow::on_selectA_clicked()
{

    this->ui->selectA->setStyleSheet("color:white;background:blue");
    this->ui->selectB->setStyleSheet("color:black;background:white");
    this->ui->selectC->setStyleSheet("color:black;background:white");
   this->ui->selectA->setCheckable(true);
    this->ui->selectA->setChecked(true);//只能设置一个
    this->ui->selectA->setAutoExclusive(true);
    //this->ui->stackPage->setCurrentIndex(0);
    qDebug()<<"page 1";
    qDebug()<<"page 1 finish";
    drawPic(1,0,34,187,2);
//    connect(this->ui->year,SIGNAL(clicked()), this, SLOT(drawPic(1,0,34,187,1)));
//    connect(this->ui->month,SIGNAL(clicked()), this, SLOT(drawPic(1,0,34,187,2)));
//    connect(this->ui->week,SIGNAL(clicked()), this, SLOT(drawPic(1,0,34,187,3)));
//    connect(this->ui->day,SIGNAL(clicked()), this, SLOT(drawPic(1,0,34,187,4)));
}

void MainWindow::on_selectB_clicked()
{
    this->ui->selectB->setStyleSheet("color:white;background:blue");
    this->ui->selectA->setStyleSheet("color:black;background:white");
    this->ui->selectC->setStyleSheet("color:black;background:white");
    this->ui->selectB->setCheckable(true);
     this->ui->selectB->setChecked(true);//只能设置一个
     this->ui->selectB->setAutoExclusive(true);
    //this->ui->stackPage->setCurrentIndex(0);
    qDebug()<<"page 2";
    //qDebug()<<"page 1 finish";
    drawPic(2,0,205,0,2);
}

void MainWindow::on_selectC_clicked()
{
    this->ui->selectC->setStyleSheet("color:white;background:blue");
    this->ui->selectA->setStyleSheet("color:black;background:white");
    this->ui->selectB->setStyleSheet("color:black;background:white");
    this->ui->selectC->setCheckable(true);
     this->ui->selectC->setChecked(true);//只能设置一个
     this->ui->selectC->setAutoExclusive(true);
    //this->ui->stackPage->setCurrentIndex(0);
    qDebug()<<"page 3";
    //qDebug()<<"page 1 finish";
    drawPic(3,238,99,99,2);
}



void MainWindow::on_year_clicked()
{
     this->ui->year->setCheckable(true);
     this->ui->year->setChecked(true);//只能设置一个
     this->ui->year->setAutoExclusive(true);
    if(this->ui->selectA->isChecked()){
        drawPic(1,0,34,187,1);
    }else if(this->ui->selectB->isChecked()){
        drawPic(2,0,205,0,1);
    }else if(this->ui->selectC->isChecked()){
        drawPic(3,238,99,99,1);
    }
}

void MainWindow::on_month_clicked()
{
    this->ui->month->setCheckable(true);
    this->ui->month->setChecked(true);//只能设置一个
    this->ui->month->setAutoExclusive(true);
   if(this->ui->selectA->isChecked()){
       qDebug()<<"monnnnnnnnnnnnnnnn";
       drawPic(1,0,34,187,2);
   }else if(this->ui->selectB->isChecked()){
       drawPic(2,0,205,0,2);
   }else if(this->ui->selectC->isChecked()){
       drawPic(3,238,99,99,2);
   }
}

void MainWindow::on_week_clicked()
{
    this->ui->week->setCheckable(true);
    this->ui->week->setChecked(true);//只能设置一个
    this->ui->week->setAutoExclusive(true);
   if(this->ui->selectA->isChecked()){
       drawPic(1,0,34,187,3);
   }else if(this->ui->selectB->isChecked()){
       drawPic(2,0,205,0,3);
   }else if(this->ui->selectC->isChecked()){
       drawPic(3,238,99,99,3);
   }
}

void MainWindow::on_day_clicked()
{
    this->ui->day->setCheckable(true);
    this->ui->day->setChecked(true);//只能设置一个
    this->ui->day->setAutoExclusive(true);
   if(this->ui->selectA->isChecked()){
       drawPic(1,0,34,187,4);
   }else if(this->ui->selectB->isChecked()){
       drawPic(2,0,205,0,4);
   }else if(this->ui->selectC->isChecked()){
       drawPic(3,238,99,99,4);
   }
}
