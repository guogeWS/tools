#ifndef GLOBALTOOL_H
#define GLOBALTOOL_H

#include <QObject>
#include <QPaintDevice>
#include <QDebug>
#include <QApplication>
#include <QScreen>
class GlobalTool:public QObject
{
    Q_OBJECT
public:
    GlobalTool();
    Q_INVOKABLE QString slipText(QString text);
    Q_INVOKABLE float getScale();
};

#endif // GLOBALTOOL_H
