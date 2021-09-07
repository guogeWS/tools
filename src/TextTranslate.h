#ifndef TEXTTRANSLATE_H
#define TEXTTRANSLATE_H
#include <QObject>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QHttpPart>
#include <QNetworkReply>
class TextTranslate
{
public:
    TextTranslate();
    QString translateFunction(QString message);
private:
    QString salt="123456";
    QString appId="20210326000743097";
    QString key="v5ndi_zBQqAD9Br20VOE";
    QString fromLanguage="en";//"en"
    QString toLanguage="zh";

};

#endif // TEXTTRANSLATE_H
