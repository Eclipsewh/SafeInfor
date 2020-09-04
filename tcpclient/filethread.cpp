#include "filethread.h"
#include<QFile>
#include<QProcess>
#include<QTextStream>
#include<QDebug>
#include<QStringList>

void fileThread::run()
{
    QFile file("./info1.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
   //主机名1
    qDebug()<<"search";
   QStringList ans;
                  QProcess p;
                  p.start("cmd", QStringList()<<"/c"<<"nmap --script nmap-vulners -sV "<<curAddress);
                  p.waitForStarted();
                  p.waitForFinished();
                  QString cmdInfo=QString::fromLocal8Bit(p.readAllStandardOutput());
                  int pos=0;
                  while(pos<cmdInfo.size()&&pos!=-1){
                      int num_last = cmdInfo.indexOf("CVE");//匹配文本的最后一个的位置
                      pos=num_last;
                      if(pos==-1)break;
                      else pos+=3;
                      QString str = cmdInfo.mid(num_last,-1);
                      QStringList list = str.split("\n");
                      ans.append(list[0]);
                  }
                  out<<ans.size()<<endl;
                  qDebug()<<ans.size()<<"CVE";
                  for(int i=0;i<ans.size();++i)out<<ans[i]<<endl;

}

//fileThread::fileThread()
//{

//}
