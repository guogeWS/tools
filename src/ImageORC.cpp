#include "ImageORC.h"

ImageORC::ImageORC(){
    screen=QGuiApplication::primaryScreen();
    trans=new TextTranslate();
}
ImageORC::ImageORC(QQmlApplicationEngine *parent)
{
    engine=parent;
    screen=QGuiApplication::primaryScreen();
    trans=new TextTranslate();
}
void ImageORC::connectServer(QString ip,int port){
    socket->connectToHost(ip,port);
    connect(socket,&QTcpSocket::readyRead,this,&ImageORC::getAnalyzeMessage);
}
void ImageORC::disconnectServer(){
    socket->close();
    socket->disconnect();
}
void ImageORC::getAnalyzeMessage(){
    QByteArray message = socket->readAll();
    message.replace("\n"," ");
    qDebug()<<"get message"<<message;
    QString transMessage=trans->translateFunction(QString(message));
    emit getText(QString(transMessage));
}
void ImageORC::getGrabText(){
    grabImage();
    postMessage(openImageFile());
}
void ImageORC::getGrabTextByXY(float x,float y,float width ,float height){
    grabImagebyXY( x, y , width , height);
    //getAccessKey();
    //postMessage(openImageFile());
    postMessage_person(openImageFile());
}
QByteArray ImageORC::grabImagebyXY(float x, float y ,float width ,float height){
    QByteArray message;
    QPixmap image= screen->grabWindow(0,x,y,width,height);
    QPixmap scaled=image.scaled(image.width()*2,image.height()*2);
    scaled.save("test.jpg","JPG");
    return message ;
}
QByteArray ImageORC::grabImage(){
    QByteArray message;
    QPixmap image= screen->grabWindow(0,engine->rootObjects()[0]->property("x").value<float>(),engine->rootObjects()[0]->property("y").value<float>()
            ,engine->rootObjects()[0]->property("width").value<float>(),engine->rootObjects()[0]->property("height").value<float>());
    //image.scaled(image.width()*2,image.height()*2);
    QPixmap scaled=image.scaled(image.width()*2,image.height()*2);
    scaled.save("test.jpg","JPG");
    return message ;
}
QByteArray ImageORC::openImageFile(){
    QFile file("test.jpg");
    if(file.open(QIODevice::ReadOnly)){
        QByteArray imageStream=file.readAll();
        QByteArray imageStream_base64=imageStream.toBase64();
        QByteArray imageStream_base64_urlEncode=QUrl::toPercentEncoding(imageStream_base64);
        return imageStream;//imageStream_base64_urlEncode;
    }else{
        return "";
    }
}
//获取access_key
void ImageORC::getAccessKey(){
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QUrl url("https://aip.baidubce.com/oauth/2.0/token");
    QNetworkRequest request(url);
    QNetworkAccessManager manager;
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded;charset=UTF-8"));
    QNetworkReply *reply = manager.post(request,QString("grant_type=client_credentials&client_id="+api_key+"&client_secret="+secret_key+"&").toLatin1());
    multiPart->setParent(reply); // delete the multiPart with the reply
    QEventLoop eventLoop;
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    QByteArray result=reply->readAll();
    qDebug()<<"get access key"<<result;
}
void ImageORC::postMessage_person(QByteArray message){
    socket->write("ImageStart");
    socket->write(message);
    socket->write("ImageEnd");
}
void ImageORC::postMessage(QByteArray message){
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QUrl url(base_process);
    QNetworkRequest request(url);
    QNetworkAccessManager manager;
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded;charset=UTF-8"));
    QNetworkReply *reply = manager.post(request, QString("access_token="+access_key+"&image="+message+"&language_type=ENG").toLatin1());
    multiPart->setParent(reply); // delete the multiPart with the reply
    QEventLoop eventLoop;
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    QByteArray result=reply->readAll();
    int starIndex=result.indexOf('[')+1;
    int endIndex=result.indexOf(']');
    result=result.mid(starIndex,endIndex-starIndex);
    QList<QByteArray> wordList=result.split(',');
    QByteArray returnMessage;
    for(int i=0;i<wordList.length();i++){
        QByteArray tempMessage=wordList[i];
        tempMessage=tempMessage.mid(tempMessage.indexOf(':'));
        int index1=tempMessage.indexOf('\"')+1;
        int index2=tempMessage.indexOf('\"',index1);
        tempMessage=tempMessage.mid(index1,index2-index1);
        wordList[i]=tempMessage;
        returnMessage+=tempMessage+" ";
    }
    //qDebug()<<"return message:"<<returnMessage;
    QString transMessage=trans->translateFunction(QString(returnMessage));
    qDebug()<<"aaaaa"<<transMessage;
    emit getText(QString(returnMessage));
    //qDebug()<<"result:"<<returnMessage ;
}
