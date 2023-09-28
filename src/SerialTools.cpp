#include "SerialTools.h"
#include <QDebug>
SerialTools::SerialTools()
{
    serial = new QSerialPort(this);
    connect(serial,&QSerialPort::readyRead,this,&SerialTools::receiveMessage);
}
void SerialTools::openSerial(){
    serial->setBaudRate(115200);
    serial->setPortName("COM5");
    serial->open(QIODevice::ReadWrite);
}
void SerialTools::receiveMessage(){
    QByteArray message = serial->readAll();
    emit messageReceived(message);
}
void SerialTools::sendMessage(QByteArray message){
    serial->write(message);
}
