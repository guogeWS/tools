#include "FileManger.h"
#include "QDebug"
FileManger::FileManger()
{

}
QString FileManger::getFileName(QString filePath){
    QFileInfo file(filePath);
    return file.fileName();
}
void FileManger::makeDir(QString pathName, QString dirName){
     QDir dir(pathName);
     dir.mkdir(dirName);
}
