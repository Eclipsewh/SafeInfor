#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "info.h"
#include <QMainWindow>
#include<QSplineSeries>
#include <QChartView>
#include <QChart>
#include<QLabel>
#include<QSqlDatabase>
#include <QTcpServer> //监听套接字
#include <QTcpSocket> //通信套接字//对方的(客户端的)套接字(通信套接字)
#include "windows.h"
#include<QList>
#include<QCheckBox>
QT_CHARTS_USE_NAMESPACE
#include<QThread>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
friend class fileThread;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //槽函数
    void on_ask1_clicked();

    void on_evaluate1_clicked();

    void on_feedback2_clicked();

    //通信用函数
    void  socket(int,int);
    void acceptConnection();
    void readClient();

    void showInfo(INFO*);
    void evaluate();//评估
    void feedback();//反馈

    void drawPic(int,int,int,int,int);
    QString getTime();
    int findPos(QString);//寻找之前存储的位置
    void on_selectA_clicked();

    void on_selectB_clicked();

    void on_selectC_clicked();

   // void on_selectA_pressed();

    void on_year_clicked();

    void on_month_clicked();

    void on_week_clicked();

    void on_day_clicked();

    void paoma();

    void anmi(QLabel *l1,QLabel *l2,QLabel *l3,QLabel *l4,QLabel *l5);
     //int find_min(int a,int b,int c,int d);

    void report(int);

    void on_ask2_clicked();

    void on_evaluate1_2_clicked();

    void on_feedback1_clicked();

    void manage();

    void sendback1();
    void sendback2();
    void sendback3();

    void on_ask2_2_clicked();


    void ColumnInit();

    void on_evaluate1_3_clicked();

    void on_feedback3_clicked();

    void on_seaButtom_clicked();

    QList<int> findoutList(int);

    void on_evaButtom_clicked();

    void on_manButtom_clicked();

private:
    QSqlDatabase db;
    Ui::MainWindow *ui;   //主界面

 //   Ui::MainWindow *login;//登录

    //INFO info[MAX_PC];
    QList<INFO>info[MAX_PC];
    int num_of_pc = 0;
    QChartView *chartview;
    QSplineSeries *series[5];
    //void sendback(int);

public:
   // int opt;
    QTcpServer *server;
    QTcpSocket *clientConnection;
    QTcpSocket *send;

    int pcIndex;
    int manIndex;


    QCheckBox *pCheckBox[MAX_PC] ;
    QCheckBox *pCheckBoxEva[MAX_PC];
    QCheckBox *pCheckBoxMan[MAX_PC];


};
#endif // MAINWINDOW_H



