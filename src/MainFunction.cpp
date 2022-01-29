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
    setRunningState(STOPED);
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
    setRunningState(RUNNING);
}
void MainFunction::startFunction(){
    workThread.start();
    timer.start(3000);
    if(orc->connectServer(_ipAddress,1234)){
        setRunningState(RUNNING);
    }
}
void MainFunction::closeFunction(){
    workThread.exit();
    timer.stop();
    orc->disconnectServer();
    setRunningState(STOPED);
}
void MainFunction::showText(QString rawMessage, QString transMessage){
    qDebug()<<"analyz message :"<<transMessage;
    setAnalyzeText(transMessage);
    setRawText(rawMessage);
    //engine->rootObjects()[0]->setProperty("orcText",message);
}
void MainFunction::getGrabText(){
    if(_grabEnable){
        orc->getGrabTextByXY(_targetX,_targetY,_targetWidth,_targetHeight);
        //orc->grabImagebyXY(_targetX,_targetY,_targetWidth,_targetHeight);
    }
}
