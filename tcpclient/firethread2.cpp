#include "firethread2.h"

//fireThread2::fireThread2(QString a)
//{

//}
#include<QFile>
#include<QProcess>
#include<QTextStream>
#include<QDebug>
#include<QStringList>

void fireThread2::run()
{
    QFile file("./info2.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    find_save(out);

}

void fireThread2::cut(QTextStream& out,QString str,QString &cmd){
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


void fireThread2::find_save( QTextStream& out){

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
