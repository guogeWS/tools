#include "ImageStitching.h"
#include "GlobalTool.h"
ImageStitching::ImageStitching()
{
//    work=new ScreencapWork();
//    work->screencapCount=0;
}
void ImageStitching::screenClip(){
    screencapCount=0;
    screencapTimer.setInterval(3000);
    setCollecting(true);
    connect(&screencapTimer,&QTimer::timeout,this,&ImageStitching::screencap);
    screencapTimer.start();
}
void ImageStitching::startWork(){
    QString path=_imageDir;
    QDir dir(path);
    QStringList nameList = dir.entryList();
    for(int i=0;i<nameList.length();i++){
        imageNameList.append(path + nameList[i]);
    }
    setMergeing(true);
    for(int i=_startPage;i<=_endPage;i++){
        QString nameA=_imageDir +QString::number(i)+"-A.jpg";
        QString nameB=_imageDir +QString::number(i)+"-B.jpg";
        QString nameC=_imageDir +QString::number(i)+"-C.jpg";
        QString nameD=_imageDir +QString::number(i)+"-D.jpg";
        setProgress((i-_startPage)*100/(_endPage-_startPage));

        if(imageNameList.contains(nameA)&&imageNameList.contains(nameB)&&imageNameList.contains(nameC)&&imageNameList.contains(nameD)){
            stitchFunction(nameA,nameB,nameC,nameD,i);
        }
    }
    setMergeing(false);
}
void ImageStitching::stitchFunction(QString nameA, QString nameB, QString nameC, QString nameD,int index){
    QPixmap sourceImage1;
    QPixmap sourceImage2;
    QPixmap sourceImage3;
    QPixmap sourceImage4;
    sourceImage1.load(nameA,"png");
    sourceImage2.load(nameB,"png");
    sourceImage3.load(nameC,"png");
    sourceImage3=sourceImage3.copy(0,sourceImage3.height()*0.1,sourceImage3.width(),sourceImage3.height()*0.9);
    sourceImage4.load(nameD,"png");
    sourceImage4=sourceImage4.copy(0,sourceImage4.height()*0.1,sourceImage4.width(),sourceImage4.height()*0.9);
    QPixmap result(sourceImage1.width()*2,2920);
    mainImage=&result;
    painter->begin(mainImage);
    painter->drawPixmap(0,0,sourceImage1.width(),sourceImage1.height(),sourceImage1);
    painter->drawPixmap(sourceImage1.width(),0,sourceImage2.width(),sourceImage2.height(),sourceImage2);
    painter->drawPixmap(0,mainImage->height()-sourceImage3.height(),sourceImage3.width(),sourceImage3.height(),sourceImage3);
    painter->drawPixmap(sourceImage1.width(),mainImage->height()-sourceImage4.height(),sourceImage4.width(),sourceImage4.height(),sourceImage4);
    mainImage->save(QString::number(index) + ".jpg");
    painter->end();
    //painter->end();
    //delete mainImage;
}
void ImageStitching::screencap(){
    QStringList cmd;
    int pageCount=(screencapCount/4)+_startPage;
    setProgress((pageCount-_startPage)*100/(_endPage-_startPage));
    qDebug()<<"_progerss progress"<<_progress;
    if(pageCount>_endPage){
        setCollecting(false);
        screencapTimer.stop();
        return;
    }
    int chipCount=screencapCount%4+1;
    qDebug()<<"pageCount"<<pageCount;
    switch (chipCount) {
    case 1:
        cmd=QStringList() << "/c" <<QString("c:/adb/adb.exe exec-out screencap -p > %3/%1-%2.jpg").arg(pageCount).arg("A").arg(_imageDir);
        break;
    case 2:
        cmd=QStringList() << "/c" <<QString("c:/adb/adb.exe exec-out screencap -p > %3/%1-%2.jpg").arg(pageCount).arg("C").arg(_imageDir);
        break;
    case 3:
        cmd=QStringList() << "/c" <<QString("c:/adb/adb.exe exec-out screencap -p > %3/%1-%2.jpg").arg(pageCount).arg("B").arg(_imageDir);
        break;
    case 4:
        cmd=QStringList() << "/c" <<QString("c:/adb/adb.exe exec-out screencap -p > %3/%1-%2.jpg").arg(pageCount).arg("D").arg(_imageDir);
        break;
    default:
        break;
    }
    myProcess->start("cmd.exe",cmd);
    myProcess->waitForFinished();
    GlobalTool::msecSleep(1000);
    myProcess->start("c:/adb/adb.exe shell input keyevent  25");
    myProcess->waitForFinished();
    screencapCount++;
}
void ImageStitching::sleep(int msec){
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
void ImageStitching::stopWork(){

}
void ImageStitching::stopScreenClip(){
    screencapTimer.stop();
    setCollecting(false);
}
void ScreencapWork::run(){
    QStringList cmd;
    int pageCount=(screencapCount/4)+1;
    int chipCount=screencapCount%4+1;
    switch (chipCount) {
    case 1:
        cmd=QStringList() << "/c" <<QString("adb exec-out screencap -p > C:\\images\\%1-%2.jpg").arg(pageCount).arg("A");
        break;
    case 2:
        cmd=QStringList() << "/c" <<QString("adb exec-out screencap -p > C:\\images\\%1-%2.jpg").arg(pageCount).arg("C");
        break;
    case 3:
        cmd=QStringList() << "/c" <<QString("adb exec-out screencap -p > C:\\images\\%1-%2.jpg").arg(pageCount).arg("B");
        break;
    case 4:
        cmd=QStringList() << "/c" <<QString("adb exec-out screencap -p > C:\\images\\%1-%2.jpg").arg(pageCount).arg("D");
        break;
    default:
        break;
    }
    myProcess->start("cmd.exe",cmd);
    myProcess->waitForFinished();
    myProcess->start("adb shell input keyevent  25");
    myProcess->waitForFinished();
    sleep(1000);
    screencapCount++;
}
