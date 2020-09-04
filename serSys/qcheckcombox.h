#ifndef QCHECKCOMBOX_H
#define QCHECKCOMBOX_H
#include<QComboBox>

class QCheckCombox
{
public:
    QCheckCombox();
    void append(QString name);
    void updateStatus(int);

};

#endif // QCHECKCOMBOX_H
