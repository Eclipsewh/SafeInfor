#ifndef SOCKET_H
#define SOCKET_H
#include <QTcpServer> //监听套接字
#include <QTcpSocket> //通信套接字//对方的(客户端的)套接字(通信套接字)
extern QTcpSocket *tcpClient;
extern QString message;  //存放从服务器接收到的字符串
#endif // SOCKET_H
