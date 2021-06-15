#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "FileManger.h"
#include "WindowsExcelfileAnalyzer.h"
#include "ImageStitching.h"
#include "GlobalTool.h"
#include "InitApp.h"
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSystemTrayIcon>
#include <QQuickWindow>
QObject * getGloalToolsFunction(QQmlEngine* ,QJSEngine *){
    GlobalTool* tools=new GlobalTool();
    return tools;
}
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    app.setOrganizationName(u8"郭哥ws");
    app.setOrganizationDomain(u8"中国");
    app.setApplicationName(u8"工具集");
    QQmlApplicationEngine engine;
    InitApp *initApp=new InitApp(&engine);
    qmlRegisterType<FileManger>               ("FileManager"               ,1 ,0    ,"FileManager");
    qmlRegisterType<WindowsExcelFileAnalyzer> ("WindowsExcelFileAnalyzer"  ,1 ,0    ,"WindowsExcelFileAnalyzer");
    qmlRegisterType<ImageStitching>           ("ImageStitching"            ,1 ,0    ,"ImageStitching");
    qmlRegisterSingletonType<GlobalTool>      ("GlobalTool"                ,1 ,0    ,"GlobalTool"          ,getGloalToolsFunction);
    engine.addImportPath("qrc:/qmlComponents");
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;
    int exitCode=app.exec();
    initApp->exitApp();
    return exitCode;
}

