#ifndef FILEMANGER_H
#define FILEMANGER_H
#include <QObject>
#include <QFile>
#include <QFileInfo>

class FileManger:public QObject
{
    Q_OBJECT
public:
    FileManger();
    Q_INVOKABLE QString getFileName(QString filePath);
};

#endif // FILEMANGER_H
