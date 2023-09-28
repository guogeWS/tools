#ifndef TCPTOOLS_H
#define TCPTOOLS_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>

class TcpTools:public QObject
{
    Q_OBJECT
    //客户端IP地址
    Q_PROPERTY(QString      ipAddress           READ ipAddress          WRITE setIpAddress          NOTIFY ipAddressChanged)
    Q_PROPERTY(int          serverPort          READ serverPort         WRITE setServerPort         NOTIFY serverPortChanged)
    Q_PROPERTY(int          socketPort          READ socketPort         WRITE setSocketPort         NOTIFY socketPortChanged)
    Q_PROPERTY(int          tcpType             READ tcpType            WRITE setTcpType            NOTIFY tcpTypeChanged)
    Q_PROPERTY(QString      localAddress        READ localAddress       WRITE setLocalAddress       NOTIFY localAddressChanged)
    //接收到的数据
    Q_PROPERTY(QByteArray   messageReceived     READ messageReceived    WRITE setMessageReceived    NOTIFY messageReceivedChanged)
    //待发送的数据
    Q_PROPERTY(QByteArray   messageSend         READ messageSend        WRITE setMessageSend        NOTIFY messageSendChanged)
    //客户端连接状态
    Q_PROPERTY(bool         socketConnectState  READ socketConnectState WRITE setSocketConnectState NOTIFY socketConnectStateChanged)
public:
    TcpTools();
    Q_INVOKABLE void connectToServer();
    Q_INVOKABLE void disconnectFromServer();
    void receiveMessage();
    Q_INVOKABLE void sendMessage(QByteArray message);

    QString     ipAddress()         {return _ipAddress;}
    int         serverPort()        {return _serverPort;}
    int         socketPort()        {return _socketPort;}
    int         tcpType()           {return _tcpType;}
    QString     localAddress()      {return _localAddress;}
    QByteArray  messageReceived()   {return _messageReceived;}
    QByteArray  messageSend()       {return _messageSend;}
    bool        socketConnectState(){return _socketConnectState;}

    void        setIpAddress(QString newValue)          {_ipAddress=newValue;emit ipAddressChanged();}
    void        setServerPort(int newValue)             {_serverPort=newValue;emit serverPortChanged();}
    void        setSocketPort(int newValue)             {_socketPort=newValue;emit socketPortChanged();}
    void        setTcpType(int newValue)                {_tcpType=newValue;emit tcpTypeChanged();}
    void        setLocalAddress(QString newValue)       {_localAddress=newValue;emit localAddressChanged();}
    void        setMessageReceived(QByteArray newValue) {_messageReceived=newValue;emit messageReceivedChanged();}
    void        setMessageSend(QByteArray newValue)     {_messageSend=newValue;emit messageSendChanged();}
    void        setSocketConnectState(bool newValue)    {_socketConnectState=newValue;emit socketConnectStateChanged();}
signals:
    void ipAddressChanged();
    void serverPortChanged();
    void socketPortChanged();
    void tcpTypeChanged();
    void localAddressChanged();
    void messageReceivedChanged();
    void messageSendChanged();
    void socketConnectStateChanged();
    void messageReceived(QByteArray message);
private:
    QTcpServer  *mainServer;//主服务器
    QTcpSocket  *mainSocket;//主客户端
    QString     _ipAddress;
    int         _serverPort;
    int         _socketPort;
    int         _tcpType;
    QString     _localAddress;
    QByteArray  _messageReceived;
    QByteArray  _messageSend;
    bool        _socketConnectState;
};

#endif // TCPTOOLS_H
