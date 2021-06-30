#include "GlobalTool.h"

GlobalTool::GlobalTool()
{
}
QString GlobalTool::slipText(QString text){
    return text.remove("file:///");
}
float GlobalTool::getScale(){
    return QApplication::primaryScreen()->logicalDotsPerInch()/96.0;
}
void GlobalTool::msecSleep(int msec){
    QTime dieTime=QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<dieTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}
void GlobalTool::msecSleep_2(int msec){
    QMutex mutex;
    QWaitCondition sleep;
    mutex.lock();
    sleep.wait(&mutex,msec);
    mutex.unlock();
}
