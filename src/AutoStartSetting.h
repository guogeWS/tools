#ifndef AUTOSTARTSETTING_H
#define AUTOSTARTSETTING_H

#include <QObject>
#include <QProcess>
#include <QFile>
#include <QDebug>
class AutoStartSetting:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
public:
    AutoStartSetting();
    Q_INVOKABLE bool    creatLink();//创建快捷方式
    QString filePath(){return _filePath;}
    void    setFilePath(QString newValue){_filePath=newValue;emit filePathChanged();}
private:
    QString    _filePath;
    QString    _fileName;
    QProcess*  cmdProcess;
signals:
    void filePathChanged();
};

#endif // AUTOSTARTSETTING_H
