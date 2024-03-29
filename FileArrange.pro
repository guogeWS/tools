QT += quick
QT += axcontainer
CONFIG += c++11
QT += widgets
QT += core
QT += sql
QT += serialport
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += src/main.cpp \
    src/FileManger.cpp \
    src/WindowsExcelfileAnalyzer.cpp \
    src/ImageStitching.cpp \
    src/GlobalTool.cpp \
    src/ApplicationPackage.cpp \
    src/InitApp.cpp \
    src/AutoStartSetting.cpp \
    src/ImageORC.cpp \
    src/MainFunction.cpp \
    src/TextTranslate.cpp \
    src/TcpTools.cpp \
    src/SerialTools.cpp

RESOURCES += qml.qrc \
    filearrange.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/FileManger.h \
    src/WindowsExcelfileAnalyzer.h \
    src/ImageStitching.h \
    src/GlobalTool.h \
    src/ApplicationPackage.h \
    src/InitApp.h \
    src/AutoStartSetting.h \
    src/ImageORC.h \
    src/MainFunction.h \
    src/TextTranslate.h \
    src/TcpTools.h \
    src/SerialTools.h

INCLUDEPATH +=   \
    src/qmlComponent

RC_FILE += FileArrange.rc

