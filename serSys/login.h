#ifndef LOGIN_H
#define LOGIN_H
#include"zhuce.h"
#include <QMainWindow>
#include<mainwindow.h>
namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    int LoginIn();
private slots:
    void on_push_clicked();

    void on_pushButton_clicked();

private:

    Ui::Login *ui;
    MainWindow w;
    zhuce zc;
};

#endif // LOGIN_H
