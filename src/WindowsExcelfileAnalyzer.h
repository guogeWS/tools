#ifndef WINDOWSEXCELFILEANALYZER_H
#define WINDOWSEXCELFILEANALYZER_H

#include <QObject>
#include <QAxObject>
#include <QDebug>
class WindowsExcelFileAnalyzer
{
    struct DailyWorkInfo
    {
        QString name;
        QString summaryOfTodayWork;
        QString tomorrowWorkPlan;
    };
public:
    WindowsExcelFileAnalyzer();
    void readExcelFile(QString fileName);
};

#endif // WINDOWSEXCELFILEANALYZER_H
