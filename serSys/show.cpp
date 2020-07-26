#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  "socket.h"
#include <QDebug>

#include <QString>
#include <QTableWidget>
#include <QTableWidgetItem>

#include<QSplineSeries>
//#include<QtCharts>

#include<QCategoryAxis>
#include <QChartView>
#include <QChart>
QT_CHARTS_USE_NAMESPACE
#define MAXSERIES 5
//#define QT_CHARTS_USE_NAMESPACE

//show 文件用来把安全信息显示到表格里
/*
typedef struct{
    int index;
    QString pcname;
    QString ip;
    bool firewall;
    bool connected;
}INFO;
*/
QString bool2String(bool b);
void MainWindow::showInfo(INFO* cur)
{

    qDebug()<<"showinfo\n"<<cur->index;
    this->ui->table->setItem(cur->index-1,0,new QTableWidgetItem(cur->pcname));
    this->ui->table->setItem(cur->index-1,1,new QTableWidgetItem(cur->ip));
    this->ui->table->setItem(cur->index-1,2,new QTableWidgetItem(bool2String(cur->firewall)));
    this->ui->table->setItem(cur->index-1,3,new QTableWidgetItem(bool2String(cur->connected)));
    this->ui->table->setItem(cur->index-1,4,new QTableWidgetItem(cur->time));
    this->ui->table->setItem(cur->index-1,5,new QTableWidgetItem(QString::number(cur->score)));
//    this->ui->table->setItem(index,1,new QTableWidgetItem(info[index].pcname));
//    this->ui->table->setItem(index,2,new QTableWidgetItem(info[index].ip));
//    this->ui->table->setItem(index,3,new QTableWidgetItem(bool2String(info[index].firewall)));
//    this->ui->table->setItem(index,4,new QTableWidgetItem(bool2String(info[index].connected)));
   this->ui->table->show();
    //info[index];

}

QString bool2String(bool b){
    if(b==true)return QString("Y");
    else return QString("N");
}

int MainWindow::findPos(QString pcname){  //查找pcname存在哪，找不到则返回0
    for(int i=1;i<=num_of_pc;++i){
        if(info[i][1].pcname==pcname)return i;
    }
    return -1;
}


int GetYear(QString tt){//获取日期
    int t = 0;
    int flag = 0;
    for(int i=0;i<tt.size();++i){
        if(tt[i]=='/')++flag;
        if(flag==1){
            qDebug()<<"year"<<t;
            return t;
        }
        if(flag==0){
        t*=10;
        t+=(tt[i].unicode()-'0');
        }
    }
    return t;
}
int GetMonth(QString tt){//获取日期
    int t = 0;
    int flag = 0;
    for(int i=0;i<tt.size();++i){
        if(tt[i]=='/')++flag;
        if(flag==2){
            qDebug()<<"month"<<t;
            return t;
        }
        if(flag==1&&tt[i]!='/'){
        t*=10;
        t+=(tt[i].toLatin1()-'0');
        }
    }
    return t;
}

int GetDay(QString tt){//获取日期
    int t = 0;
    int flag = 0;
    for(int i=0;i<tt.size();++i){
        if(tt[i]=='/')++flag;
        if(flag==3){
            qDebug()<<"day"<<t;return t;

        }if(flag==2&&tt[i]!='/'){
        t*=10;
        qDebug()<<tt[i].unicode()<<" "<<(int)'0';
        t+=(tt[i].unicode()-'0');
        }
    }
    return t;
}

int GetHour(QString tt){//获取日期
    int t = 0;
    int flag = 0;
    for(int i=0;i<tt.size();++i){
        if(tt[i]=='/')++flag;
        if(flag==4){
            qDebug()<<"hour"<<t;
            return t;
        }
            if(flag==3&&tt[i]!='/'){
        t*=10;
        t+=(tt[i].unicode()-'0');
        }
    }
    return t;
}

int GetWeek(QString tt){//获取日期
    int t = 0;
    //int flag = 0;
        for(int i=0;i<tt.size();++i){
           QChar ch = tt.at(i);
           if(ch=="一")t=1;
           if(ch=="二")t=2;
           if(ch=="三")t=3;
           if(ch=="四")t=4;
           if(ch=="五")t=5;
           if(ch=="六")t=6;
           if(ch=="日")t=7;
        }
        qDebug()<<"week"<<t;
        return t;
    }

void MainWindow::drawPic(int index,int p1,int p2,int p3,int k)
{
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->setTitle("安全线曲线图");
    //QSplineSeries *series[5] ;//= (QSplineSeries *)malloc(5*sizeof(QSplineSeries));//new QSplineSeries();//曲线图
    //delete series[index];
    series[index] = new QSplineSeries();
    series[index]->setVisible(true);
  qDebug()<<"si111";
  qDebug()<<info[index].size()-1;
    for(int i=1;i<=info[index].size()-1;++i){
            if(k==1)series[index]->append(GetMonth(info[index][i].time),info[index][i].score);
            if(k==2)series[index]->append(GetDay(info[index][i].time),info[index][i].score);
            if(k==3)series[index]->append(GetWeek(info[index][i].time),info[index][i].score);
            if(k==4)series[index]->append(GetHour(info[index][i].time),info[index][i].score);

        }

    //series->append(1,60);
    qDebug()<<"si";
    series[index]->append(2,87);
    series[index]->setColor(QColor(p1,p2,p3));
    series[index]->setName(QString("设备" + QString::number(index)));

    series[index]->setPointLabelsVisible(true);
    series[index]->setPointLabelsColor(QColor(p1,p2,p3));
    chart->addSeries(series[index]);

    //chart->createDefaultAxes();
     chart->legend()->setVisible(true);//设置是否可视
  //   chart->axisY()->setRange(0,100);
    // axisX = new QValueAxis;
     QValueAxis *axisX = new QValueAxis();
     QValueAxis *axisY = new QValueAxis();
     if(k==1){
         axisX->setTickCount(12); //会划分成几个单位·
         axisX->setRange(1,12);
         axisX->setLabelFormat("%d"); //设置刻度的格式
     }
     if(k==2){
         axisX->setTickCount(31); //会划分成几个单位·
         axisX->setRange(1,31);
         axisX->setLabelFormat("%d"); //设置刻度的格式
         //chart->axisX()->setRange(1,32);
     }
     if(k==3){
         axisX->setTickCount(7); //会划分成几个单位·
         axisX->setRange(1,7);
         axisX->setLabelFormat("%d"); //设置刻度的格式
         //chart->axisX()->setRange(1,7);
     }
     if(k==4){
         axisX->setTickCount(6); //会划分成几个单位·
         axisX->setRange(0,24);
         axisX->setLabelFormat("%d"); //设置刻度的格式
         //chart->axisX()->setRange(1,24);
     }
     axisY->setRange(0,100);
   // chart->setAxisX(axis, series);
    //  axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
     //  axisY->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
     //chart->addAxis(xAxis, Qt::AlignBottom);
     //chart->addAxis(yAxis, Qt::AlignLeft);
     chart->setAxisX(axisX,series[index]);
     chart->setAxisY(axisY,series[index]);
    this->ui->widget1->setChart(chart);
    // this->ui->widget1->setCentralWidget(nchartview);
    this->ui->widget1->resize(700, 420);
    //   while(1){

    this->ui->widget1->show();

}

