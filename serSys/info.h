#ifndef INFO_H
#define INFO_H
#include<QDebug>
#include <QDialog>
typedef struct{
    int index;
    QString pcname;
    QString ip;
    bool firewall;
    bool connected;
    int cnt;
    QString time;
    double score;
}INFO;

#endif // INFO_H
