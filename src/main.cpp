#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "FileManger.h"
#include "WindowsExcelfileAnalyzer.h"
#include <QDir>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    app.setOrganizationName(u8"郭哥ws");
    app.setOrganizationDomain(u8"中国");
    app.setApplicationName(u8"工具集");
    QQmlApplicationEngine engine;
    qmlRegisterType<FileManger>("FileManager" ,1 ,0,"FileManager");
    qmlRegisterType<WindowsExcelFileAnalyzer>("WindowsExcelFileAnalyzer",1,0,"WindowsExcelFileAnalyzer");
    engine.addImportPath("qrc:/qmlComponents");
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
