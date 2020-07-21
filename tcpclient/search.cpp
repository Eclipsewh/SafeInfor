//用于查询
#include<QtDebug>
#include  "socket.h"
#include "widget.h"
//#include<stdio.h>
#include <QProcess>
#include <string>
#include <QTextStream>
bool checkFileWall(std::string info);

void Widget::search(){

    QFile file("./info.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
   //主机名1
    qDebug()<<"search";
    QString localHost = QHostInfo::localHostName();
    qDebug()<<localHost;
 //   file.write(localHost.toUtf8());
   out<<localHost<<endl;
 //  out<<'#'<<endl;
 //IP2
   QHostInfo info = QHostInfo::fromName(localHost);
  // qDebug()<<"IP Address："<< info.addresses();
 // out<<'#'<<endl;

   foreach(QHostAddress address,info.addresses())
      {
          if(address.protocol() == QAbstractSocket::IPv4Protocol)
              //QString addr = address.toString();
              qDebug()<<address.toString()<<endl;
              std::string addr  = address.toString().toStdString();
              if(addr[0]=='1'&&addr[1]=='9'&&addr[2]=='2'){
                  //file.write(address.toString().toUtf8());
                  //调用cmd
                  QProcess p;
                  p.start("cmd", QStringList()<<"/c"<<"nmap -sA "<<address.toString());
                  p.waitForStarted();
                  p.waitForFinished();

                  QString cmdInfo=QString::fromLocal8Bit(p.readAllStandardOutput());
                  bool fireOn = checkFileWall(cmdInfo.toStdString());//防火墙是否打开
                  //ip3 fire3
                  out<<address.toString()<<endl;
                  out<<fireOn<<endl;
                 qDebug()<<"防火墙开启"<<fireOn;
                  qDebug() <<"My localhost IPv4 address: "<< address.toString();
                  break;
              }

      }
  //  out<<'#'<<endl;// 分隔符

    //QNetworkConfigurationManager provides access to the network configurations
    //known to the system and enables applications to detect the system capabilities
    //(with regards to network sessions) at runtime.

    //上网5
     QNetworkConfigurationManager mgr;
     out<<mgr.isOnline();
     qDebug()<<"能否上网"<<mgr.isOnline()<<endl;
  //   out<<'#'<<endl;// 分隔符

    file.close();


}

bool checkFileWall(std::string info)
{
    std::string on = "filtered";
    std::string off = "unfiltered";
    for(int i=0;i<info.length()-on.length();++i){
        std::string get1 = info.substr(i,8);
        std::string get2 = info.substr(i,10);
        if(get2 == off)return false;
        if(get1 == on)return true;
    }
    return false;
}
