#include "ImageStitching.h"

ImageStitching::ImageStitching()
{

}
void ImageStitching::startWork(){
    QString path=_imageDir;
    QDir dir(path);
    QStringList nameList = dir.entryList();
    for(int i=0;i<nameList.length();i++){
        imageNameList.append(path + nameList[i]);
    }
    for(int i=1;i<100;i++){
        QString nameA="C:/FileArrange/source/image/"+QString::number(i)+"-A.jpg";
        QString nameB="C:/FileArrange/source/image/"+QString::number(i)+"-B.jpg";
        QString nameC="C:/FileArrange/source/image/"+QString::number(i)+"-C.jpg";
        QString nameD="C:/FileArrange/source/image/"+QString::number(i)+"-D.jpg";
        if(imageNameList.contains(nameA)&&imageNameList.contains(nameB)&&imageNameList.contains(nameC)&&imageNameList.contains(nameD))
        stitchFunction(nameA,nameB,nameC,nameD,i);
    }
}
void ImageStitching::stitchFunction(QString nameA, QString nameB, QString nameC, QString nameD,int index){
    QPixmap sourceImage1;
    QPixmap sourceImage2;
    QPixmap sourceImage3;
    QPixmap sourceImage4;
    sourceImage1.load(nameA);
    sourceImage2.load(nameB);
    sourceImage3.load(nameC);
    sourceImage3=sourceImage3.copy(0,sourceImage3.height()*0.1,sourceImage3.width(),sourceImage3.height()*0.9);
    sourceImage4.load(nameD);
    sourceImage4=sourceImage4.copy(0,sourceImage4.height()*0.1,sourceImage4.width(),sourceImage4.height()*0.9);
    QPixmap *mainImage=new QPixmap(sourceImage1.width()*2,2910);
    QPainter painter(mainImage);
    painter.drawPixmap(0,0,sourceImage1.width(),sourceImage1.height(),sourceImage1);
    painter.drawPixmap(sourceImage1.width(),0,sourceImage2.width(),sourceImage2.height(),sourceImage2);
    painter.drawPixmap(0,mainImage->height()-sourceImage3.height(),sourceImage3.width(),sourceImage3.height(),sourceImage3);
    painter.drawPixmap(sourceImage1.width(),mainImage->height()-sourceImage4.height(),sourceImage4.width(),sourceImage4.height(),sourceImage4);
    mainImage->save(QString::number(index) + ".jpg");
}
