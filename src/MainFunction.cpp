#include "MainFunction.h"
MainFunction::MainFunction(){
    orc=new ImageORC();
    orc->moveToThread(&workThread);
    workThread.start();
    QObject::connect(&timer,&QTimer::timeout,this,&MainFunction::getGrabText);
    QObject::connect(orc,&ImageORC::getText,this,&MainFunction::showText);
    timer.start(3000);
    trans=new TextTranslate();
}

MainFunction::MainFunction(QQmlApplicationEngine *parent)
{
    engine=parent;
    ImageORC *orc=new ImageORC(parent);
    orc->moveToThread(&workThread);
    workThread.start();
    QObject::connect(&timer,&QTimer::timeout,orc,&ImageORC::getGrabText);
    QObject::connect(orc,&ImageORC::getText,this,&MainFunction::showText);
    timer.start(3000);
    trans=new TextTranslate();
}
void MainFunction::showText(QString message){
    qDebug()<<"analyz message :"<<message;
    //engine->rootObjects()[0]->setProperty("orcText",message);
}
void MainFunction::getGrabText(){
    if(_grabEnable){
        orc->getGrabTextByXY(_targetX,_targetY,_targetWidth,_targetHeight);
        //orc->grabImagebyXY(_targetX,_targetY,_targetWidth,_targetHeight);
    }
}
