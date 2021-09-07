#include "TextTranslate.h"
#include <QTextCodec>
#include <QCryptographicHash>
TextTranslate::TextTranslate()
{
    //translateFunction("this is a car ,this is a apple");
}
QString TextTranslate::translateFunction(QString message){
    QUrl url("https://fanyi-api.baidu.com/api/trans/vip/translate");
    QNetworkRequest request(url);
    QNetworkAccessManager manager;
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));
    QString sign=appId+message+salt+key;
    QString sign_md5= QString(QCryptographicHash::hash(sign.toLatin1(),QCryptographicHash::Md5).toHex());
    QString parameter = QString("q=%1&from=%2&to=%3&appid=%4&salt=%5&sign=%6").arg(message).arg(fromLanguage).arg(toLanguage).arg(appId).arg(salt).arg(sign_md5);
    QNetworkReply *reply = manager.post(request, parameter.toLatin1());
    QEventLoop eventLoop;
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    QByteArray result=reply->readAll();
    int starIndex=result.indexOf("dst");
    result=result.mid(starIndex);
    starIndex=result.indexOf(":");
    result=result.mid(starIndex+1);
    starIndex=result.indexOf("\"");
    result=result.mid(starIndex+1);
    starIndex=result.indexOf("\"");
    result=result.mid(0,starIndex);

    QString resultString=QString(result);

    do {
        int idx = resultString.indexOf("\\u");
        QString strHex = resultString.mid(idx, 6);
        strHex = strHex.replace("\\u", QString());
        int nHex = strHex.toInt(0, 16);
        resultString.replace(idx, 6, QChar(nHex));
    } while (resultString.indexOf("\\u") != -1);
    //qDebug()<<"result :"<<resultString;
    return resultString;
}
