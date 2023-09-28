#include "TcpTools.h"

TcpTools::TcpTools()
{
    mainSocket = new QTcpSocket(this);
    connect(mainSocket,&QTcpSocket::readyRead,this,&TcpTools::receiveMessage);
}
void TcpTools::connectToServer(){
    mainSocket->connectToHost(_ipAddress,_socketPort);
    if(mainSocket->waitForConnected(3000)){
        qDebug()<<"success";
    }else{
        qDebug()<<"failed";
    }
}
void TcpTools::disconnectFromServer(){
    mainSocket->disconnectFromHost();
}
void TcpTools::receiveMessage(){
    QByteArray message = mainSocket->readAll();
    //message = message.toHex();
    setMessageReceived(message);
    emit messageReceived(message);
}
void TcpTools::sendMessage(QByteArray message){
    QByteArray cookedMessage = message;//QByteArray::fromHex(message);
    mainSocket->write(cookedMessage);
}
