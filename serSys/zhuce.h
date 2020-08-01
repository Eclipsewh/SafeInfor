#ifndef ZHUCE_H
#define ZHUCE_H

#include <QMainWindow>

namespace Ui {
class zhuce;
}

class zhuce : public QMainWindow
{
    Q_OBJECT

public:
    explicit zhuce(QWidget *parent = nullptr);
    ~zhuce();

private slots:
    void on_pushButton_clicked();

private:
    Ui::zhuce *ui;
};

#endif // ZHUCE_H
