#ifndef WINDOWSEXCELFILEANALYZER_H
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
    Q_PROPERTY(int analyzeType READ analyzeType WRITE setAnalyzeType NOTIFY analyzeTypeChanged)
    //Q_PROPERTY(int todayIndex READ todayIndex WRITE setTodayIndex NOTIFY todayIndexChanged)//今日工作总结的序号
public:
    WindowsExcelFileAnalyzer();
    int  analyzeType(){return _analyzeType;}
    void setAnalyzeType(int newValue){_analyzeType=newValue;emit analyzeTypeChanged();}


    Q_INVOKABLE void    readExcelFile(QString fileName);
    Q_INVOKABLE void    writeExcelFile(QString fileName);
    Q_INVOKABLE QString outPutToTxtFile(QString fileName);
    Q_INVOKABLE void    setCurrentData(QString year,QString mounth,QString data){
        _currentData=data;
        _currentYear=year;
        _currentMounth=mounth;
    }
    Q_INVOKABLE void setTargetFile(QString target){
        _targetFile=target;
    }
    Q_INVOKABLE void getUsefulFile(QString path);
    Q_INVOKABLE QString slipText(QString text);
    QList<DailyWorkInfo> infoList;
    QMap<QString,DailyWorkInfo> infoMap;
    QString _currentData="";
    QString _currentYear="";
    QString _currentMounth="";
    QString _targetFile;
private:
    int _analyzeType;//解析模式  0：  1；
    int nameNum=4;//姓名数量
    int nameLineCount=1;//姓名所在的列序号
    int workSumaryFirstIndex=10;//今日工作总结序号
    int tomorrowWorkFirstIndex=15;//明日工作计划序号
signals:
    void analyzeTypeChanged();
};

#endif // WINDOWSEXCELFILEANALYZER_H
