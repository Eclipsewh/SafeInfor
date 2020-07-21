#ifndef INFO_H
#define INFO_H
#include<QDebug>
#include <QDialog>

typedef struct{
    QString pcname;
    QString ip;
    bool firewall;
    bool connected;
}INFO;
#endif // INFO_H
