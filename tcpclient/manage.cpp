#include "manage.h"
#include<QMessageBox>
#include<QProcess>
#include <QTcpServer> //监听套接字
#include <QTcpSocket> //通信套接字//对方的(客户端的)套接字(通信套接字)
manage::manage()
{

}
/*

1-----------sfc /scannow 系统扫描
2-----------防火墙开启
3-----------防火墙关闭
*/

void Widget::manage(int opt)
{


//    QTcpSocket *clientConnection;
//    if( server->listen(QHostAddress::Any,8888))connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    qDebug()<<"opt"<<opt<<" "<<opt+'0';
  //  search();
    if(opt==4){
        QMessageBox msgBox;
        msgBox.setText("是否进行系统扫描验证");
        msgBox.setWindowTitle("管理操作");
        msgBox.setStandardButtons(QMessageBox::Cancel|QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();

        if(ret==QMessageBox::Yes){
            QProcess p;

        //    p.start("cmd", QStringList()<<"runas /user:wys cmd");
            p.start("cmd", QStringList()<<"/c"<<"sfc /scannow");
            p.waitForStarted();
            p.waitForFinished();
            QString cmdInfo=QString::fromLocal8Bit(p.readAllStandardOutput());
            qDebug()<<cmdInfo;
        }
    }
        if(opt==2){
            QMessageBox msgBox;
            msgBox.setText("是否开启防火墙");
            msgBox.setStandardButtons(QMessageBox::Cancel|QMessageBox::Yes);
            msgBox.setDefaultButton(QMessageBox::Yes);
            int ret = msgBox.exec();

            if(ret==QMessageBox::Yes){
                QProcess p;
                p.start("cmd", QStringList()<<"/c"<<"netsh advfirewall set allprofiles state on");
                p.waitForStarted();
                p.waitForFinished();
                //QString cmdInfo=QString::fromLocal8Bit(p.readAllStandardOutput());
                QMessageBox::information(this,"成功","防火墙已开启");
            }
        }

        if(opt==3){
            QMessageBox msgBox;
            msgBox.setText("是否关闭防火墙");
            msgBox.setStandardButtons(QMessageBox::Cancel|QMessageBox::Yes);
            msgBox.setDefaultButton(QMessageBox::Yes);
            int ret = msgBox.exec();

            if(ret==QMessageBox::Yes){
                QProcess p;
                p.start("cmd", QStringList()<<"/c"<<"netsh advfirewall set allprofiles state off");
                p.waitForStarted();
                p.waitForFinished();
                //QString cmdInfo=QString::fromLocal8Bit(p.readAllStandardOutput());
                QMessageBox::information(this,"成功","防火墙已关闭");
            }
        }





}



