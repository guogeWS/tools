#ifndef GLOBALTOOL_H
#define GLOBALTOOL_H

#include <QObject>
#include <QPaintDevice>
#include <QDebug>
#include <QApplication>
#include <QScreen>
#include <QTime>
#include <QMutex>
#include <QWaitCondition>
class GlobalTool:public QObject
{
    Q_OBJECT
public:
    GlobalTool();
    Q_INVOKABLE QString slipText(QString text);
    Q_INVOKABLE float getScale();
    static void msecSleep(int msec);
    void msecSleep_2(int msec);
};

#endif // GLOBALTOOL_H
