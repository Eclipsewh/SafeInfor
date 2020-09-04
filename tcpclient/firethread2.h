#ifndef FIRETHREAD2_H
#define FIRETHREAD2_H
#include<QThread>
#include<QTextStream>
class fireThread2:public QThread
{
public:
    fireThread2(QString a){
        curAddress = a;
    }
    void run()override;
    QString curAddress;
    QTextStream cmd;
    void find_save( QTextStream&);//查找内存
    void cut(QTextStream&,QString,QString &cmd);
};


#endif // FIRETHREAD2_H
