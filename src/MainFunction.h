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
signals:
    void targetXChanged();
    void targetYChanged();
    void targetWidthChanged();
    void targetHeightChanged();
    void grabEnableChanged();
public:
    MainFunction();
    MainFunction(QQmlApplicationEngine *parent);
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
};

#endif // MAINFUNCTION_H
