#ifndef APPLICATIONPACKAGE_H
#define APPLICATIONPACKAGE_H
#include <QObject>
#include <QProcess>
#include <QDebug>
class ApplicationPackage:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
    Q_PROPERTY(QString qmlLibPath READ qmlLibPath WRITE setQmlLibPath NOTIFY qmlLibPathChanged)
public:

    ApplicationPackage();
    Q_INVOKABLE void copyQtFile();
    Q_INVOKABLE void copyQtFile2();
    QString filePath(){return _filePath;}
    void    setFilePath(QString newValue){_filePath=newValue;emit filePathChanged();}
    QString qmlLibPath(){return _qmlLibPath;}
    void    setQmlLibPath(QString value){ _qmlLibPath=value;emit qmlLibPathChanged();}
private:
    QString    _filePath;
    QString    _qmlLibPath;
    QProcess*  cmdProcess;
signals:
    void filePathChanged();
    void qmlLibPathChanged();
};

#endif // APPLICATIONPACKAGE_H
