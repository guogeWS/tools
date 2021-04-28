#ifndef IMAGESTITCHING_H
#define IMAGESTITCHING_H
#include <QObject>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QDir>
class ImageStitching:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString imageDir READ imageDir WRITE setImageDir NOTIFY imageDirChanged)
public:
    ImageStitching();
    QString imageDir(){return _imageDir;}
    void setImageDir(QString newValue){_imageDir=newValue;emit imageDirChanged();}
    Q_INVOKABLE void startWork();
    void stitchFunction(QString nameA,QString nameB,QString nameC,QString nameD,int index);

private:
    QString _imageDir;
    QImage img;
    QStringList imageNameList;//图片名称列表
signals:
    void imageDirChanged();
};

#endif // IMAGESTITCHING_H
