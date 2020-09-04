#ifndef INFO_H
#define INFO_H
#include<QDebug>
#include <QDialog>
#define MAX_PC 30
#include "windows.h"
#include<QThread>
//int fileindex;
#include<QList>
//int pc2chose;
typedef struct{
    QString port_num;
    QString service;
}duankou;

typedef struct{
    int index;
    QString pcname;
    QString ip;
    bool firewall;
    bool connected;
    int cnt;
    QString time;
    double score;
    QString physical;       //实际内存
    QString vir;            //虚拟内存
    QList<duankou>port;//端口
    int portNum;//端口数目
    QString type;//型号
    QList<QString>CVE;
    int cveNum;
}INFO;

class FThread:public QThread
{
    Q_OBJECT
  public:
    FThread(INFO _cur){cur = _cur;};
public:
    INFO cur;
public slots:
    void run();


};
#endif // INFO_H
