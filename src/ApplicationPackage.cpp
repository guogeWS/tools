#include "ApplicationPackage.h"

ApplicationPackage::ApplicationPackage()
{
    cmdProcess=new QProcess();
}
void ApplicationPackage::copyQtFile(){
    QStringList cmd;
    cmd=QStringList() << "/c" <<QString("windeployqt %1").arg(_filePath);
    cmdProcess->start("cmd.exe",cmd);
    cmdProcess->waitForFinished();
}
void ApplicationPackage::copyQtFile2(){
    QStringList cmd;
    cmd=QStringList() << "/c" <<QString("windeployqt %1 --qmldir %2").arg(_filePath).arg(_qmlLibPath);
    //cmd=QStringList() << "/c" << "windeployqt" << _filePath ;//<< "--qmldir" << _qmlLibPath ;
    qDebug()<<"cmd cmd"<<cmd;
    cmdProcess->start("cmd.exe",cmd);
    cmdProcess->waitForFinished();
}
