#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "info.h"
#include <QMainWindow>

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


    void evaluate();//评估
    void feedback();//反馈

private:
    Ui::MainWindow *ui;   //主界面
    Ui::MainWindow *login;//登录
    INFO info[MAX_PC];
    int num_of_pc = 0;
};
#endif // MAINWINDOW_H
