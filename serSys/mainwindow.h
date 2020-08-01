#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "info.h"
#include <QMainWindow>
#include<QSplineSeries>
#include <QChartView>
#include <QChart>
#include<QLabel>
#include<QSqlDatabase>
QT_CHARTS_USE_NAMESPACE
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
#define MAX_PC 20
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //槽函数
    void on_ask1_clicked();

    void on_evaluate1_clicked();

    void on_feedback2_clicked();

    //通信用函数
    void  socket();
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

private:
    QSqlDatabase db;
    Ui::MainWindow *ui;   //主界面
 //   Ui::MainWindow *login;//登录
    QList<INFO>info[MAX_PC];
    //INFO info[MAX_PC];
    int num_of_pc = 0;
    QChartView *chartview;
    QSplineSeries *series[5];


};
#endif // MAINWINDOW_H
