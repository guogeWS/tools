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
    Q_PROPERTY(int nameNumQML READ nameNumQML WRITE setNameNumQML NOTIFY nameNumQMLChanged)
    Q_PROPERTY(int nameLineCountQML READ nameLineCountQML WRITE setNameLineCountQML NOTIFY nameLineCountQMLChanged)
    Q_PROPERTY(int workIndex READ workIndex WRITE setWorkIndex NOTIFY workIndexChanged)
    Q_PROPERTY(int tommIndex READ tommIndex WRITE setTommIndex NOTIFY tommIndexChanged)
    Q_PROPERTY(int dataLineCountQML READ dataLineCountQML WRITE setDataLineCountQML NOTIFY dataLineCountQMLChanged)
public:
    WindowsExcelFileAnalyzer();
    int  analyzeType(){return _analyzeType;}
    void setAnalyzeType(int newValue){_analyzeType=newValue;emit analyzeTypeChanged();}
    int  nameNumQML(){return nameNum;}
    void setNameNumQML(int newValue){nameNum=newValue;emit nameNumQMLChanged();}
    int  nameLineCountQML(){return nameLineCount;}
    void setNameLineCountQML(int newValue){nameLineCount=newValue;emit nameLineCountQMLChanged();}
    int  workIndex(){return workSumaryFirstIndex;}
    void setWorkIndex(int newValue){workSumaryFirstIndex=newValue;emit workIndexChanged();}
    int  tommIndex(){return tomorrowWorkFirstIndex;}
    void setTommIndex(int newValue){tomorrowWorkFirstIndex=newValue;emit tommIndexChanged();}
    int  dataLineCountQML(){return dataLineCount;}
    void setDataLineCountQML(int newValue){dataLineCount=newValue;emit dataLineCountQMLChanged();}


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
    int dataLineCount=11;//日期所在列序号
    int nameLineCount=1;//姓名所在的列序号
    int workSumaryFirstIndex=12;//今日工作总结序号
    int tomorrowWorkFirstIndex=19;//明日工作计划序号
signals:
    void analyzeTypeChanged();
    void nameNumQMLChanged();
    void nameLineCountQMLChanged();
    void workIndexChanged();
    void tommIndexChanged();
    void dataLineCountQMLChanged();
};

#endif // WINDOWSEXCELFILEANALYZER_H
