#ifndef AUTOSTARTSETTING_H
#define AUTOSTARTSETTING_H

#include <QObject>
#include <QProcess>
#include <QFile>
class AutoStartSetting:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
public:
    AutoStartSetting();
    Q_INVOKABLE void    creatLink();//创建快捷方式
    QString filePath(){return _filePath;}
    void    setFilePath(QString newValue){_filePath=newValue;emit filePathChanged();}
private:
    QString    _filePath;
    QProcess*  cmdProcess;
signals:
    void filePathChanged();
};

#endif // AUTOSTARTSETTING_H
