#include <QAxWidget>
#include <QAxObject>
#include<QProcess>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QAxWidget>
#include <QAxObject>
#include <QFile>
#include "windows.h"
//QtWebKitWidgets/QWebView
void MainWindow::report(int index)
{
    qDebug()<<"获取报告1";
    // 新建一个word应用程序,并设置为不可见
    //ksolaunch
    //QAxWidget *word=new QAxWidget("ksolaunch.exe", 0, Qt::MSWindowsOwnDC);
     QAxWidget *word=new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    word->setProperty("Visible", false);
    // 获取所有的工作文档
    qDebug()<<"获取报告2";
    QAxObject * documents = word->querySubObject("Documents");

    // 以文件template.dot为模版新建一个文档
    //documents->dynamicCall("Add(QString)",QString(":/template.dot"));
    documents->dynamicCall("Add(QString)",QString("D:/QT5.12/serSys/template.dot"));

    //pcname
    QAxObject *document=word->querySubObject("ActiveDocument");
    // 获取文档中名字为label1的标签
    QAxObject*bookmark_pcname=document->querySubObject("Bookmarks(pcname)");
    // 选中标签，将字符InsertText插入到标签位置
    if(!bookmark_pcname->isNull())
    {
        bookmark_pcname->dynamicCall("Select(void)");
        bookmark_pcname->querySubObject("Range")->setProperty("Text",info[index][info[index][1].cnt].pcname);
    }

    qDebug()<<"获取报告3";
    QAxObject*bookmark_score=document->querySubObject("Bookmarks(score)");
    // 选中标签，将字符InsertText插入到标签位置
    if(!bookmark_score->isNull())
    {
        bookmark_score->dynamicCall("Select(void)");
        bookmark_score->querySubObject("Range")->setProperty("Text",QString::number(info[index][info[index][1].cnt].score));
    }

    QAxObject*bookmark_ip=document->querySubObject("Bookmarks(ip)");
    // 选中标签，将字符InsertText插入到标签位置
    if(!bookmark_ip->isNull())
    {
        bookmark_ip->dynamicCall("Select(void)");
        bookmark_ip->querySubObject("Range")->setProperty("Text",info[index][info[index][1].cnt].ip);
    }

    QAxObject*bookmark_time=document->querySubObject("Bookmarks(time)");
    // 选中标签，将字符InsertText插入到标签位置
    if(!bookmark_time->isNull())
    {
        bookmark_time->dynamicCall("Select(void)");
        bookmark_time->querySubObject("Range")->setProperty("Text",info[index][info[index][1].cnt].time);
    }

    QAxObject*firewall=document->querySubObject("Bookmarks(firewall)");
    QString res;
    if(info[index][info[index][1].cnt].firewall)res = "是";
    else res = "否";
    // 选中标签，将字符InsertText插入到标签位置
    if(!firewall->isNull())
    {
        firewall->dynamicCall("Select(void)");
        firewall->querySubObject("Range")->setProperty("Text",res);
    }

    QAxObject*c=document->querySubObject("Bookmarks(connect)");
    // 选中标签，将字符InsertText插入到标签位置
    if(info[index][info[index][1].cnt].connected)res = "是";
    else res = "否";

     qDebug()<<"获取报告4";
    if(!c->isNull())
    {
       c->dynamicCall("Select(void)");
       c->querySubObject("Range")->setProperty("Text",res);
    }
//    // 获取文档中名字为label2的标签
//    QAxObject *bookmark_pic = document->querySubObject("Bookmarks(label2)");
//    // 选中标签，将图片插入到标签位置
//    if(!bookmark_pic->isNull())
//    {
//        bookmark_pic->dynamicCall("Select(void)");
//        QAxObject *Inlineshapes = document->querySubObject("InlineShapes");
//        Inlineshapes->dynamicCall("AddPicture(const QString&)","D:\\123.jpg");  //路径必须为windows路径格式
//    }

    // 将文件另存为docbyqt.doc,关闭工作文档，退出应用程序
    document->dynamicCall("SaveAs (const QString&)", QString("D:/QT5.12/serSys/report.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");


    QProcess p;
    p.start("cmd", QStringList()<<"D:\\QT5.12\\serSys\\report.doc");
    p.waitForStarted();
    p.waitForFinished();
    //delete bookmark_name;
   // delete bookmark_pic;
    delete document;
    delete documents;
    delete word;

//    return 0;



}
