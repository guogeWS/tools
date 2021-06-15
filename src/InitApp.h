#ifndef INITAPP_H
#define INITAPP_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
class InitApp:public QObject
{
public:
    InitApp(QQmlApplicationEngine *parent);
    void exitApp();
    void maxWindow();
    void minWindow();
    void normWindow();
    void activeFunction(QSystemTrayIcon::ActivationReason reason);
private:
    QSystemTrayIcon *systemarayicon;
    QQmlApplicationEngine *parentEngine;
};

#endif // INITAPP_H
