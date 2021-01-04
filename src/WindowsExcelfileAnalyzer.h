﻿#ifndef WINDOWSEXCELFILEANALYZER_H
#define WINDOWSEXCELFILEANALYZER_H

#include <QObject>
#include <QAxObject>
#include <QDebug>
#include <QFile>
#include <QDir>
class WindowsExcelFileAnalyzer:public QObject
{
    Q_OBJECT
    struct DailyWorkInfo
    {
        QString name;
        QString summaryOfTodayWork;
        QString summaryOfTodayWork_simple;
        QString tomorrowWorkPlan;
    };
public:
    WindowsExcelFileAnalyzer();
    Q_INVOKABLE void readExcelFile(QString fileName);
    Q_INVOKABLE void writeExcelFile(QString fileName);
    Q_INVOKABLE void outPutToTxtFile(QString fileName);
    Q_INVOKABLE void setCurrentData(QString year,QString mounth,QString data){
        _currentData=data;
        _currentYear=year;
        _currentMounth=mounth;
    }
    Q_INVOKABLE void getUsefulFile(QString path);
    QList<DailyWorkInfo> infoList;
    QMap<QString,DailyWorkInfo> infoMap;
    QString _currentData="";
    QString _currentYear="";
    QString _currentMounth="";
};

#endif // WINDOWSEXCELFILEANALYZER_H
