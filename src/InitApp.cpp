#include "InitApp.h"

InitApp::InitApp(QQmlApplicationEngine *parent)
{
    parentEngine=parent;
    systemarayicon=new QSystemTrayIcon();
    systemarayicon->setIcon(QIcon(":/img/images/tools.png"));
    systemarayicon->setToolTip(u8"工具集");
    systemarayicon->show();
    connect(systemarayicon,&QSystemTrayIcon::activated,this,&InitApp::activeFunction);
}
void InitApp::activeFunction(QSystemTrayIcon::ActivationReason reason){
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        normWindow();
        break;
    default:
        break;
    }

}
void InitApp::exitApp(){
    systemarayicon->hide();
}
void InitApp::minWindow(){
    ((QQuickWindow *)(parentEngine->rootObjects()[0]))->showMinimized();
}
void InitApp::maxWindow(){
    ((QQuickWindow *)(parentEngine->rootObjects()[0]))->showMaximized();
}
void InitApp::normWindow(){
    ((QQuickWindow *)(parentEngine->rootObjects()[0]))->showNormal();
}
