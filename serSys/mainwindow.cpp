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
#include<QTimer>
#include "info.h"
#include<QtWidgets>
#include<QCheckBox>
#include<QListWidgetItem>
#include<QPropertyAnimation>
QT_CHARTS_USE_NAMESPACE
//mainwindow 负责一个主要功能的展示，对应pptNo2
//void anmi(QLabel *l1,QLabel *l2,QLabel *l3,QLabel *l4);
//主界面
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    setWindowIcon(QIcon(":/SuCai/logo.png"));
    //setWindowTitle("SafeManager");
   // setWindowIconText("安全管理系统");
    //setWindowOpacity();
    this->ui->setupUi(this);
    //this->ui->setupUi(this->login);
    qDebug()<<"showinfo  mainwindow\n";
    this->ui->tabWidget->setWindowOpacity(0.7);
    paoma();
    QMovie *iconShow = new QMovie(":/SuCai/tecLine.gif");
    //QMovie *iconShow = new QMovie(":/SuCai/back1.gif");
    //QMovie *iconShow = new QMovie(":/SuCai/mov1.gif");
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


         QTimer *timer = new QTimer(this);
         connect(timer, SIGNAL(timeout()), this,SLOT(paoma()));
         //anmi(this->ui->paoma1,this->ui->paoma2,this->ui->paoma3,this->ui->paoma4);
         timer->start(2000);

         ColumnInit();


}

void MainWindow::ColumnInit(){
    int numOfpc = 30;
    for (int i = 0; i < numOfpc; ++i)
       {
           QListWidgetItem *pItem = new QListWidgetItem(this->ui->sealist);
           QListWidgetItem *pItemEva = new QListWidgetItem(this->ui->evalist);
           QListWidgetItem *pItemMan = new QListWidgetItem(this->ui->manlist);
           this->ui->sealist->addItem(pItem);
           this->ui->evalist->addItem(pItemEva);
           this->ui->manlist->addItem(pItemMan);
           if (i == 0)
           {
               pItem->setData(Qt::UserRole, i - 1);
               pItemEva->setData(Qt::UserRole, i - 1);
               pItemMan->setData(Qt::UserRole, i - 1);
           }
           else
           {
               pItem->setData(Qt::UserRole, i);//data数据可作为参数
               pItemEva->setData(Qt::UserRole, i);//data数据可作为参数
               pItemMan->setData(Qt::UserRole, i);//data数据可作为参数
           }
//           QCheckBox *pCheckBox = new QCheckBox(this);
//           QCheckBox *pCheckBoxEva = new QCheckBox(this);
//           QCheckBox *pCheckBoxMan = new QCheckBox(this);

           pCheckBox[i] = new QCheckBox(this);
           pCheckBoxEva[i] = new QCheckBox(this);
           pCheckBoxMan[i] = new QCheckBox(this);



           QString txt = tr("设备%1").arg(i+1);
           pCheckBox[i]->setText(txt);
           pCheckBox[i]->setStyleSheet("color:blue");//设置下拉选项的文本颜色
           pCheckBox[i]->setChecked(false);


           pCheckBoxEva[i]->setText(txt);
           pCheckBoxEva[i]->setStyleSheet("color:blue");//设置下拉选项的文本颜色
           pCheckBoxEva[i]->setChecked(false);


           pCheckBoxMan[i]->setText(txt);
           pCheckBoxMan[i]->setStyleSheet("color:blue");//设置下拉选项的文本颜色
           pCheckBoxMan[i]->setChecked(false);


           this->ui->sealist->addItem(pItem);
           this->ui->sealist->setItemWidget(pItem, pCheckBox[i]);//复选框嵌入QListWidget

           this->ui->evalist->addItem(pItemEva);
           this->ui->evalist->setItemWidget(pItemEva, pCheckBoxEva[i]);//复选框嵌入QListWidget

           this->ui->manlist->addItem(pItemMan);
           this->ui->manlist->setItemWidget(pItemMan, pCheckBoxMan[i]);//复选框嵌入QListWidget
           //响应状态变化
           //connect(pCheckBox, SIGNAL(stateChanged(int)), this, SLOT(stateChanged(int)));
       }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ask1_clicked()
{
    qDebug()<<("socket");
    socket(8888,1);  //开始通信


}

void MainWindow::on_evaluate1_clicked()
{
    //report(1);
    //fileindex =  1;
//    pc2chose = 1;
//    INFO cur;
//    qDebug()<<info[1][1].cnt<<"第几个";
//    cur = info[1][info[1][1].cnt];
//    FThread *newThread= new FThread(cur);
//    //newThread->cur = cur;
//    newThread->start();
    report(1);
    evaluate();//评估开始
}

void MainWindow::on_feedback2_clicked()
{
    manIndex = 2;
    manage();
    //feedback();//反馈
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

void MainWindow::paoma(){
    this->ui->paoma1->show();
    this->ui->paoma2->show();
    this->ui->paoma3->show();
    this->ui->paoma4->show();
    this->ui->paoma1->setMaximumWidth(4000);
     this->ui->paoma2->setMaximumWidth(4000);
     this->ui->paoma3->setMaximumWidth(4000);
     this->ui->paoma4->setMaximumWidth(4000);

//    this->ui->paoma1->setMaximumHight(50);
//     this->ui->paoma2->setMaximumHight(50);

//     this->ui->paoma3->setMaximumHight(50);
//     this->ui->paoma4->setMaximumHight(50);
    if(this->ui->paoma1->text().isEmpty()||num_of_pc>0){
        if(num_of_pc!=0){
            int i=1;
            //while(i<=num_of_pc){
                this->ui->paoma1->setText(info[i][1].pcname);
                this->ui->paoma2->setText(info[i][1].ip);
                this->ui->paoma3->setText(QString("firewall connected:")+QString(info[i][1].firewall));
                this->ui->paoma4->setText(QString("network connected:")+QString(info[i][1].connected));
              //  QTimer *timer = new QTimer(this);
               // connect(timer, SIGNAL(timeout()), this,SLOT(anmi(this->ui->paoma1,this->ui->paoma2,this->ui->paoma3,this->ui->paoma4)));

                //anmi(this->ui->paoma1,this->ui->paoma2,this->ui->paoma3,this->ui->paoma4);
                //timer->start(1000);
                anmi(this->ui->paoma1,this->ui->paoma2,this->ui->paoma3,this->ui->paoma4,this->ui->paoma5);
             //   ++i;
               // if(i>num_of_pc)i=1;
           // }
        }else{
            qDebug()<<"here";


            this->ui->paoma1->setText("Welcome,Users!");
            this->ui->paoma2->setText("Let us start with Wchecker");
            this->ui->paoma3->setText("Stay Safe!");
            this->ui->paoma4->setText("Keep Happy!");
//            QTimer *timer = new QTimer(this);
//            connect(timer, SIGNAL(timeout()), this,SLOT(anmi(this->ui->paoma1,this->ui->paoma2,this->ui->paoma3,this->ui->paoma4)));
//            timer->start(1000);
               anmi(this->ui->paoma1,this->ui->paoma2,this->ui->paoma3,this->ui->paoma4,this->ui->paoma5);
        }
    }else{
     anmi(this->ui->paoma1,this->ui->paoma2,this->ui->paoma3,this->ui->paoma4,this->ui->paoma5);
    }

}

void appearL(QLabel *l1,QLabel *l2,QLabel *l3,QLabel *l4){
l1->show();
l2->show();
l3->show();
l4->show();
}

void MainWindow::anmi(QLabel *l1,QLabel *l2,QLabel *l3,QLabel *l4,QLabel *l5){ //590 610 630 650
   // qDebug()<<"anima";
    QPropertyAnimation *pAnimation1 = new QPropertyAnimation(l1, "geometry");
    QPropertyAnimation *pAnimation2 = new QPropertyAnimation(l2, "geometry");
    QPropertyAnimation *pAnimation3 = new QPropertyAnimation(l3, "geometry");
    QPropertyAnimation *pAnimation4 = new QPropertyAnimation(l4, "geometry");
    QPropertyAnimation *pAnimation5 = new QPropertyAnimation(l5, "opacity");
   // QPropertyAnimation *animation;
    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    group->addAnimation(pAnimation1);
    group->addAnimation(pAnimation2);
    group->addAnimation(pAnimation3);
    group->addAnimation(pAnimation4);
group->addAnimation(pAnimation5);




    pAnimation1->setDuration(1000);
    pAnimation2->setDuration(1000);
    pAnimation3->setDuration(1000);
    pAnimation4->setDuration(1000);
    pAnimation5->setDuration(1000);


   int mm1=  l1->y()>l2->y()?l1->y():l2->y();
    int mm2=  l3->y()>l4->y()?l3->y():l4->y();
    mm1 = mm1>mm2?mm1:mm2;
    int l11 = l1->y();
    if(mm1==l1->y())l5->setText(l1->text());
    if(mm1==l2->y())l5->setText(l2->text());
    if(mm1==l3->y())l5->setText(l3->text());
    if(mm1==l4->y())l5->setText(l4->text());
    //pAnimation5->setStartValue(QRect(l1->x(),570, 150, 25));
    pAnimation5->setStartValue(0);
    pAnimation5->setEndValue(0.5);
    pAnimation5->setEasingCurve(QEasingCurve::InExpo);  // 缓和曲线风格


        pAnimation1->setStartValue(QRect(l1->x(),l1->y(), 150, 25));
        pAnimation1->setEndValue(QRect(l1->x(),l2->y(), 150, 25));
        if(l1->y()==mm1){
            qDebug()<<"1";
            l1->hide();
        }
        pAnimation1->setEasingCurve(QEasingCurve::Linear);  // 缓和曲线风格


       int width = 30000,h = 25;

        pAnimation2->setStartValue(QRect(l2->x(),l2->y(),  width,h));
        pAnimation2->setEndValue(QRect(l2->x(),l3->y(), width,h));
        if(l2->y()==mm1){
            qDebug()<<"2";
            l2->hide();
        }
        pAnimation2->setEasingCurve(QEasingCurve::Linear);  // 缓和曲线风格

        pAnimation3->setStartValue(QRect(l1->x(),l3->y(),  width,h));
        pAnimation3->setEndValue(QRect(l1->x(),l4->y(),  width,h));
        if(l3->y()==mm1){
            qDebug()<<"3";
            l3->hide();
        }
        pAnimation3->setEasingCurve(QEasingCurve::Linear);  // 缓和曲线风格

        pAnimation4->setStartValue(QRect(l1->x(),l4->y(),  width,h));
        pAnimation4->setEndValue(QRect(l1->x(),l11, width,h));
        pAnimation4->setEasingCurve(QEasingCurve::Linear);  // 缓和曲线风格
        //pAnimation1->set
        if(l4->y()==mm1){
            qDebug()<<"4";
            l4->hide();
        }
  //  }
    group->start();
//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this,SLOT(appearL(l1,l2,l3,l4)));
//    //anmi(this->ui->paoma1,this->ui->paoma2,this->ui->paoma3,this->ui->paoma4);
//    timer->start(0);
//    l1->show();
//    l2->show();
//    l3->show();
//    l4->show();


    //connect(pStartButton, SIGNAL(clicked(bool)), pAnimation, SLOT(start()));
}

void MainWindow::on_ask2_clicked()
{
    qDebug()<<("socket2");
    socket(8888,2);  //开始通信
}

void MainWindow::on_evaluate1_2_clicked()
{
    report(2);
    evaluate();//评估开始
}

void MainWindow::on_feedback1_clicked()
{
    manIndex = 1;
    manage();
}



void MainWindow::on_ask2_2_clicked()
{
    qDebug()<<("socket3");
    socket(8888,3);  //开始通信
}

void MainWindow::on_evaluate1_3_clicked()
{
    report(3);
}

void MainWindow::on_feedback3_clicked()
{
    manIndex = 3;
    manage();
}

void MainWindow::on_seaButtom_clicked()
{
    QList<int> pc = findoutList(1);
    for(int i=0;i<pc.size();++i)socket(8888,pc[i]+3);
}


void MainWindow::on_evaButtom_clicked()
{
    QList<int> pc = findoutList(2);
    for(int i=0;i<pc.size();++i)report(pc[i]+4);
}

void MainWindow::on_manButtom_clicked()
{
    QList<int> pc = findoutList(3);
    for(int i=0;i<pc.size();++i){
        manIndex = pc[i]+4;
        manage();

    }
}

QList<int>  MainWindow::findoutList(int index){
    QList<int>box;
    for(int i=0;i<=30;++i){
        if(index==1){
            if(pCheckBox[i]->isChecked()){
                qDebug()<<"i "<<i;
                box.append(i);
            }
        }
        if(index==2){
            if(pCheckBoxEva[i]->isChecked())box.append(i);
        }
        if(index==3){
            if(pCheckBoxMan[i]->isChecked())box.append(i);

        }

    }
    qDebug()<<"findoutList";
    for(int i=0;i<box.size();++i)qDebug()<<box[i];
    return box;
}
