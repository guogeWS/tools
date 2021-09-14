#ifndef MAINFUNCTION_H
#define MAINFUNCTION_H
#include "ImageORC.h"
#include "TextTranslate.h"
#include <QThread>
#include <QTimer>
#include <QObject>
#include <QQmlApplicationEngine>
class MainFunction:public QObject
{
    Q_OBJECT
    QThread workThread;
    Q_PROPERTY(bool grabEnable READ grabEnable WRITE setGrabEnable NOTIFY grabEnableChanged)
    Q_PROPERTY(float targetX READ targetX WRITE setTargetX NOTIFY targetXChanged)
    Q_PROPERTY(float targetY READ targetY WRITE setTargetY NOTIFY targetYChanged)
    Q_PROPERTY(float targetWidth READ targetWidth WRITE setTargetWidth NOTIFY targetWidthChanged)
    Q_PROPERTY(float targetHeight READ targetHeight WRITE setTargetHeight NOTIFY targetHeightChanged)
    Q_PROPERTY(QString analyzeText READ analyzeText WRITE setAnalyzeText NOTIFY analyzeTextChanged)
    Q_PROPERTY(QString ipAddress READ ipAddress WRITE setIpAddress NOTIFY ipAddressChanged)
signals:
    void targetXChanged();
    void targetYChanged();
    void targetWidthChanged();
    void targetHeightChanged();
    void grabEnableChanged();
    void analyzeTextChanged();
    void ipAddressChanged();
public:
    MainFunction();
    MainFunction(QQmlApplicationEngine *parent);
    Q_INVOKABLE void startFunction();
    Q_INVOKABLE void closeFunction();
    void grabFunction();
    void showText(QString message);
    void getGrabText();
    float targetX(){return _targetX;}
    void  setTargetX(float newValue){_targetX=newValue;emit targetXChanged();}
    float targetY(){return _targetY;}
    void  setTargetY(float newValue){_targetY=newValue;emit targetYChanged();}
    float targetWidth(){return _targetWidth;}
    void  setTargetWidth(float newValue){_targetWidth=newValue;emit targetWidthChanged();}
    float targetHeight(){return _targetHeight;}
    void  setTargetHeight(float newValue){_targetHeight=newValue;emit targetHeightChanged();}
    bool  grabEnable(){return _grabEnable;}
    void  setGrabEnable(bool newValue){_grabEnable=newValue;emit grabEnableChanged();}
    QString analyzeText(){return _analyzeText;}
    void  setAnalyzeText(QString newValue){_analyzeText=newValue;emit analyzeTextChanged();}
    QString ipAddress(){return _ipAddress;}
    void  setIpAddress(QString newValue){_ipAddress=newValue;emit ipAddressChanged();}
private:
    QQmlApplicationEngine *engine;
    TextTranslate *trans;
    QTimer timer;
    float _targetX;
    float _targetY;
    float _targetWidth;
    float _targetHeight;
    ImageORC *orc;
    bool _grabEnable;
    QString _analyzeText;
    QString _ipAddress;
};

#endif // MAINFUNCTION_H
