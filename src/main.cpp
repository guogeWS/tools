#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "FileManger.h"
#include "WindowsExcelfileAnalyzer.h"
#include <QDir>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    /*
    QString currentData="31";
    WindowsExcelFileAnalyzer *excelFileAnalyzer=new WindowsExcelFileAnalyzer();
    excelFileAnalyzer->setCurrentData(currentData);
    QString path=u8"c:/Users/WIN 10/Desktop/工作计划/";
    QDir fileDir(path);
    fileDir.setFilter(QDir::Files);
    QFileInfoList fileInfoList=fileDir.entryInfoList();
    for(int i=0;i<fileInfoList.length();i++){
        QString fileName=fileInfoList.at(i).fileName();
        if(fileName.contains("2020")&&fileName.contains("12")&&fileName.contains(currentData)){
            qDebug()<<"fileName :"<<fileName;
            excelFileAnalyzer->readExcelFile(path+(fileName));
        }
    }
    path=u8"c:/Users/WIN 10/Desktop/工作计划/研发部工作情况-12月.xlsx";
    excelFileAnalyzer->writeExcelFile(path);
    path=u8"c:/Users/WIN 10/Desktop/工作计划/新建文本文档.txt";
    excelFileAnalyzer->outPutToTxtFile(path);
*/
    QQmlApplicationEngine engine;
    qmlRegisterType<FileManger>("FileManager" ,1 ,0,"FileManager");
    qmlRegisterType<WindowsExcelFileAnalyzer>("WindowsExcelFileAnalyzer",1,0,"WindowsExcelFileAnalyzer");
    engine.addImportPath("qrc:/qmlComponents");
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
