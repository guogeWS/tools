#ifndef IMAGESTITCHING_H
#define IMAGESTITCHING_H
#include <QObject>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QDir>
#include <QProcess>
#include <QTimer>
#include <QTime>
#include <QCoreApplication>
#include <QThread>
class ScreencapWork:public QThread{
    Q_OBJECT
public:
    void run() override;
    QProcess *myProcess=new QProcess();
    QTimer screencapTimer;//截屏定时器
    int screencapCount;
    int pageCount;
signals:
    void workFinished();
};
class ImageStitching:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString imageDir    READ imageDir     WRITE setImageDir   NOTIFY imageDirChanged)
    Q_PROPERTY(int     startPage   READ startPage    WRITE setStartPage  NOTIFY startPageChanged)
    Q_PROPERTY(int     endPage     READ endPage      WRITE setEndPage    NOTIFY endPageChanged)
public:
    ImageStitching();
    QString imageDir(){return _imageDir;}
    int     startPage(){return _startPage;}
    int     endPage(){return _endPage;}
    void    setImageDir(QString newValue){_imageDir=newValue;emit imageDirChanged();}
    void    setStartPage(int newValue){_startPage=newValue;emit startPageChanged();}
    void    setEndPage(int newValue){_endPage=newValue;emit endPageChanged();}
    Q_INVOKABLE void startWork();
    Q_INVOKABLE void screenClip();//采集图片碎片
    //截屏功能
    void screencap();
    void stitchFunction(QString nameA,QString nameB,QString nameC,QString nameD,int index);

private:
    QString _imageDir;
    QImage img;
    QStringList imageNameList;//图片名称列表
    QProcess *myProcess=new QProcess();
    QTimer screencapTimer;//截屏定时器
    ScreencapWork *work;
    int screencapCount;
    int pageCount;
    int _startPage=1;
    int _endPage=100;
    QPixmap  *mainImage;
    QPainter *painter=new QPainter();
    void sleep(int delay);
signals:
    void imageDirChanged();
    void startPageChanged();
    void endPageChanged();
};

#endif // IMAGESTITCHING_H
