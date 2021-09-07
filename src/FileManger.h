#ifndef FILEMANGER_H
#define FILEMANGER_H
#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QDir>

class FileManger:public QObject
{
    Q_OBJECT
public:
    FileManger();
    Q_INVOKABLE QString getFileName(QString filePath);
    Q_INVOKABLE void makeDir(QString pathName, QString dirName);
};

#endif // FILEMANGER_H
