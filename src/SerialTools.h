#ifndef SERIALTOOLS_H
#define SERIALTOOLS_H

#include <QObject>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
class SerialTools:public QObject
{
    Q_OBJECT
public:
    SerialTools();
    Q_INVOKABLE void openSerial();
    Q_INVOKABLE void sendMessage(QByteArray message);
    void receiveMessage();
private:
    QSerialPort* serial;
signals:
    void messageReceived(QByteArray message);
};

#endif // SERIALTOOLS_H
