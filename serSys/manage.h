#ifndef MANAGE_H
#define MANAGE_H
#include"mainwindow.h"
#include <QMainWindow>

namespace Ui {
class manage;
}

class manage : public QMainWindow
{
    Q_OBJECT

public:
    explicit manage(QWidget *parent = nullptr);
    ~manage();

private slots:
    void on_push_saomiao_clicked();

    void on_push_firewallon_clicked();

    void on_push_firewalloff_clicked();

private:
    Ui::manage *ui;
};

#endif // MANAGE_H
