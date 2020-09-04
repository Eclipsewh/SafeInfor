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

                  curAddress = address.toString();//保存现有地址，后面使用
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
   startThread();
   startThread2();
  //  out<<'#'<<endl;// 分隔符

    //QNetworkConfigurationManager provides access to the network configurations
    //known to the system and enables applications to detect the system capabilities
    //(with regards to network sessions) at runtime.

    //上网5
     QNetworkConfigurationManager mgr;
     out<<mgr.isOnline()<<endl;
     qDebug()<<"能否上网"<<mgr.isOnline()<<endl;
  //   out<<'#'<<endl;// 分隔符

//     find_save(out);
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


void Widget::cut(QTextStream& out,QString str,QString &cmd){
    int num_last = cmd.lastIndexOf(str);//匹配文本的最后一个的位置

   //qDebug()<<num_last;
    QString index = cmd.mid(num_last+str.size()+1,-1);
    //qDebug()<<"index"<<index;
    QStringList list = index.split("\r\n");
    QString xinghao = list[0];

//    for(int i=num_last+1;i<cmd.size();++i){
//        if(str[i]=='\n')break;
//        if(str[i]==' ')continue;
//        xinghao.append(str[i]);
//    }
    qDebug()<<str<<" "<<xinghao;
    out<<xinghao<<endl;
}


void Widget::find_save( QTextStream& out){

    QProcess p2;
    p2.start("cmd", QStringList()<<"/c"<<"nmap -sT "<<curAddress);
    p2.waitForStarted();
    p2.waitForFinished(600000);
  //  p2.waitForFinished()

    QString cmdInfo2=QString::fromLocal8Bit(p2.readAllStandardOutput());


    int num_last = cmdInfo2.lastIndexOf("SERVICE");//匹配文本的最后一个的位置
    int num_last2 = cmdInfo2.indexOf("Nmap done");//匹配文本的最后一个的位置
    qDebug()<<"numlset  "<<num_last<<" "<<cmdInfo2.size()<<" "<<curAddress;
    QString port = cmdInfo2.mid(num_last+9,num_last2-num_last-12);
    //QString QString::mid(int position, int n = -1) const
    QStringList list = port.split("\r\n");
    out<<list.size()<<endl;
    qDebug()<<"元素个数"<<list.size()<<endl;  //端口数目
    for(int i=0;i<list.size();++i){
        out<<list[i]<<endl;
        qDebug()<<list[i];
    }


    QProcess p;
    p.start("cmd", QStringList()<<"/c"<<"systeminfo");
    p.waitForStarted();
    p.waitForFinished();
    QString cmdInfo=QString::fromLocal8Bit(p.readAllStandardOutput());
    //qDebug()<<cmdInfo.shrink_to_fit();
//    QTextCodec *gbk = QTextCodec::codecForName("GB18030");
//    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");

//   // QString a = "utf8乱码";
//    char endmsg[1284] = {0};
//    memcpy(endmsg, gbk->fromUnicode(utf8->toUnicode(cmdInfo.toLatin1())).data(),128);
//    cmdInfo = endmsg;
    qDebug()<<"contanin"<<cmdInfo.contains("系统型号");
    cut(out,QString("系统型号"),cmdInfo);
    cut(out,"物理内存总量",cmdInfo);
    cut(out,"虚拟内存: 最大值",cmdInfo);



}


