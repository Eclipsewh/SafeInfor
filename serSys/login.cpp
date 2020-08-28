#include "login.h"
#include "ui_login.h"
#include<QString>
#include<QDebug>
#include<QSqlDatabase>
#include<QMovie>
#include<QSqlQuery>
#include<QMessageBox>
#include<QtWidgets>
#include <QTextLine>
#include<QMouseEvent>
Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->name->setPlaceholderText("姓名");
    ui->password->setPlaceholderText("密码");
    setWindowIcon(QIcon(":/SuCai/logo.png"));

    QMovie *iconShow = new QMovie(":/SuCai/bolang1.gif");
    //QMovie *iconShow = new QMovie(":/SuCai/back1.gif");
    //QMovie *iconShow = new QMovie(":/SuCai/mov1.gif");
    ui->mov->resize(450,300);
    ui->mov->setMovie(iconShow);
    iconShow->start();
}

Login::~Login()
{
    delete ui;
}

int Login::LoginIn()
{
     QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
      db = QSqlDatabase::addDatabase("QSQLITE");

   //= QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QApplication::applicationDirPath()+"/data.dat");
    if (!db.open()) {
            QMessageBox::warning(this,"ERROR","sql unable to connect");
            return false;
     }
    qDebug()<<"login";
     QString name = this->ui->name->text();
     QString password = this->ui->password->text();
     QSqlQuery query(db);
     QString search = QString("SELECT * FROM login WHERE name = %1;").arg(name);
     query.exec(search);
     while(query.next()){
         qDebug()<<"###############################33";
         QString nn = query.value(0).toString();
         QString pp = query.value(1).toString();
         qDebug()<<nn<<"name";
         if(nn==name&&pp==password)return 1;
     }


        return 0;


}

void Login::on_push_clicked()
{
    if(LoginIn()){
        qDebug()<<"login hide";
        this->hide();
      //  MainWindow w;
        w.setWindowTitle("WChecker");
        w.show();
    }else QMessageBox::warning(NULL,"ERROR","密码错误");
}


//void Login::mouseDoubleClickEvent(QMouseEvent *event)
//{
//    //判断是否为鼠标左键双击
//    if(event->button() == Qt::LeftButton)
//    {
//        QLabel * label = new QLabel(this);
//        QMovie * movie = new QMovie(":/Resource/effects.gif");//加载gif图片
//        //设置label自动适应gif的大小
//        label->setScaledContents(true);

//        label->setMovie(movie);
//        //这里为了调用move方便，进行resize，需要知道的是gif的大小本来也就是150*150
//        label->resize(150,150);
//        //设置鼠标穿透
//        label->setAttribute(Qt::WA_TransparentForMouseEvents, true);
//        //让label的中心在当前鼠标双击位置
//        label->move(event->pos().x()-label->width()/2,event->pos().y()-label->height()/2);
//        //开始播放gif
//        movie->start();

//        label->show();

//        //绑定QMovie的信号，判断gif播放次数
//        connect(movie, &QMovie::frameChanged, [=](int frameNumber) {
//            if (frameNumber == movie->frameCount() - 1)//gif播放次数为1，关闭标签
//                label->close();
//        });
//    }
//}




void Login::on_pushButton_clicked()
{

    QSqlDatabase db;
   if(QSqlDatabase::contains("qt_sql_default_connection"))
     db = QSqlDatabase::database("qt_sql_default_connection");
   else
     db = QSqlDatabase::addDatabase("QSQLITE");
   // QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QApplication::applicationDirPath()+"/data.dat");
    if (!db.open()) {
            QMessageBox::warning(this,"ERROR","sql unable to connect");
            //return false;
     }
    QSqlQuery query(db);
//    query.exec("CREATE TABLE login ("
//                       "name VARCHAR(40) NOT NULL, "
//                      "pzword VARCHAR(40) NOT NULL)");
   // zhuce zhuce;
//    query.prepare("INSERT TABLE login (name,pzword) "
//                      "VALUES (:name, :pzword)");
    zc.show();

}
