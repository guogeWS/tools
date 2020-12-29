#ifndef WINDOWSEXCELFILEANALYZER_H
#define WINDOWSEXCELFILEANALYZER_H

#include <QObject>
#include <QAxObject>
#include <QDebug>
#include <QFile>
class WindowsExcelFileAnalyzer
{
    struct DailyWorkInfo
    {
        QString name;
        QString summaryOfTodayWork;
        QString summaryOfTodayWork_simple;
        QString tomorrowWorkPlan;
    };
public:
    WindowsExcelFileAnalyzer();
    void readExcelFile(QString fileName);
    void writeExcelFile(QString fileName);
    void outPutToTxtFile(QString fileName);
    void setCurrentData(QString data){
        _currentData=data;
    }
    QList<DailyWorkInfo> infoList;
    QMap<QString,DailyWorkInfo> infoMap;
    QString _currentData="";
};

#endif // WINDOWSEXCELFILEANALYZER_H
