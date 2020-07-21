#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //void connect();
    void socket(); //通信用函数
    void search(); //查询用函数
    void sendFile();//文件传送函数

private slots:
    void on_send_clicked();

 //   void on_pushButton_clicked();

    void on_search_clicked();

private:
    Ui::Widget *ui;
    QTcpSocket *tcpSocket;
    QString message;  //存放从服务器接收到的字符串
};
#endif // WIDGET_H
