#ifndef SOCKET_H
#define SOCKET_H
#include <QTcpServer> //监听套接字
#include <QTcpSocket> //通信套接字//对方的(客户端的)套接字(通信套接字)

extern QTcpServer *server;
extern QTcpSocket *clientConnection;




#endif // SOCKET_H
