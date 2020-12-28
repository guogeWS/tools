#include "FileManger.h"
#include "QDebug"
FileManger::FileManger()
{

}
QString FileManger::getFileName(QString filePath){
    QFileInfo file(filePath);
    qDebug()<<"name name name"<<file.fileName();
    return file.fileName();
}
