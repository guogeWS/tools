#ifndef IMAGEORC_H
#define IMAGEORC_H
#include <QObject>
#include <QFile>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QHttpPart>
#include <QHttpMultiPart>
#include <QNetworkReply>
#include <QEventLoop>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QScreen>
#include <QPixmap>
#include <QTimer>
#include <QTcpSocket>
#include "TextTranslate.h"
// 设置APPID/AK/SK
class ImageORC:public QObject
{
    Q_OBJECT
public:
    ImageORC();
    ImageORC(QQmlApplicationEngine *parent);
    QByteArray openImageFile();
    QByteArray grabImage();
    QByteArray grabImagebyXY(float x,float y,float width ,float height);
    void       getGrabText();
    void       getGrabTextByXY(float x,float y,float width ,float height);
    void       postMessage(QByteArray message);
    void       postMessage_person(QByteArray message);
    void       getAccessKey();
    void       readAll();
    void       getAnalyzeMessage();
    bool       connectServer(QString ip,int port);//连接到ORC服务器上
    void       disconnectServer();
private:
    QStringList languageTypelist={"JAP","ENG"};
    QString app_id = "";
    QString api_key = "";
    QString secret_key = "";
    QString access_key = "";
    QString base_process="";//基本转译
    QString accurate_process="";//精确转译
    QNetworkAccessManager * netWorkManager=new QNetworkAccessManager ();
    QNetworkRequest * request=new QNetworkRequest();
    QGuiApplication *app;
    QQmlApplicationEngine *engine;
    QScreen *screen;
    QTimer timer;
    TextTranslate *trans;
    QTcpSocket *socket=new QTcpSocket();
signals:
    void getText(QString rawMessage, QString transMessage);
};

#endif // IMAGEORC_H
