#include "MainFunction.h"
MainFunction::MainFunction(){
    orc=new ImageORC();
    orc->moveToThread(&workThread);
//    workThread.start();
//    QObject::connect(&timer,&QTimer::timeout,this,&MainFunction::getGrabText);
//    QObject::connect(orc,&ImageORC::getText,this,&MainFunction::showText);
//    timer.start(3000);
    QObject::connect(&timer,&QTimer::timeout,this,&MainFunction::getGrabText);
    QObject::connect(orc,&ImageORC::getText,this,&MainFunction::showText);
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
void MainFunction::startFunction(){
    workThread.start();
    timer.start(3000);
    qDebug()<<"AAAAAAA"<<_ipAddress;
    orc->connectServer(_ipAddress,1234);
}
void MainFunction::closeFunction(){
    workThread.exit();
    timer.stop();
    orc->disconnectServer();
}
void MainFunction::showText(QString message){
    qDebug()<<"analyz message :"<<message;
    setAnalyzeText(message);
    //engine->rootObjects()[0]->setProperty("orcText",message);
}
void MainFunction::getGrabText(){
    if(_grabEnable){
        orc->getGrabTextByXY(_targetX,_targetY,_targetWidth,_targetHeight);
        //orc->grabImagebyXY(_targetX,_targetY,_targetWidth,_targetHeight);
    }
}
