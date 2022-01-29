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
    Q_PROPERTY(bool    grabEnable       READ grabEnable     WRITE setGrabEnable     NOTIFY grabEnableChanged)
    Q_PROPERTY(float   targetX          READ targetX        WRITE setTargetX        NOTIFY targetXChanged)
    Q_PROPERTY(float   targetY          READ targetY        WRITE setTargetY        NOTIFY targetYChanged)
    Q_PROPERTY(float   targetWidth      READ targetWidth    WRITE setTargetWidth    NOTIFY targetWidthChanged)
    Q_PROPERTY(float   targetHeight     READ targetHeight   WRITE setTargetHeight   NOTIFY targetHeightChanged)
    Q_PROPERTY(QString analyzeText      READ analyzeText    WRITE setAnalyzeText    NOTIFY analyzeTextChanged)
    Q_PROPERTY(QString rawText          READ rawText        WRITE setRawText        NOTIFY rawTextChanged)
    Q_PROPERTY(QString ipAddress        READ ipAddress      WRITE setIpAddress      NOTIFY ipAddressChanged)
    Q_PROPERTY(states  runningState     READ runningState   WRITE setRunningState   NOTIFY runningStateChanged)

signals:
    void targetXChanged();
    void targetYChanged();
    void targetWidthChanged();
    void targetHeightChanged();
    void grabEnableChanged();
    void analyzeTextChanged();
    void rawTextChanged();
    void ipAddressChanged();
    void runningStateChanged();
public:
    MainFunction();
    MainFunction(QQmlApplicationEngine *parent);
    enum states{
        STOPED=0,
        RUNNING=1
    };
    Q_ENUM(states)
    Q_INVOKABLE void startFunction();
    Q_INVOKABLE void closeFunction();
    void  grabFunction();
    void  showText(QString rawMessage, QString transMessage);
    void  getGrabText();
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
    QString rawText(){return _rawText;}
    void  setRawText(QString newValue){_rawText=newValue;emit rawTextChanged();}
    QString ipAddress(){return _ipAddress;}
    void  setIpAddress(QString newValue){_ipAddress=newValue;emit ipAddressChanged();}
    states runningState(){return _runningState;}
    void  setRunningState(states newValue){_runningState = newValue;emit runningStateChanged();}
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
    QString _rawText;
    QString _ipAddress;
    states  _runningState;
};

#endif // MAINFUNCTION_H
