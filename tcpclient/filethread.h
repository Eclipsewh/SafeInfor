#ifndef FILETHREAD_H
#define FILETHREAD_H
#include<QThread>
//class filethread:  public QThread
//{
//    Q_OBJECT

//signals:
//    void Ready();
//    filethread(QString a){
//        curAddress = a;
//    }
//    QString curAddress;
//public:
//void run()override;
//////emit Ready();


////};
//多线程
class fileThread:public QThread
{
    Q_OBJECT

public:
    fileThread(QString a){
        curAddress = a;
    }
    void run()override;
    QString curAddress;
};

#endif // FILETHREAD_H


