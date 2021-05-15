/*Qt应用打包*/
/*QT应用打包的一般方法
1.首先，通过relese编译生成可执行文件，如FileManager.exe
2.然后，打开控制台CMD，跳转到FileManager.exe所在的文件夹，执行命令"windeployqt FileArrange.exe",该命令会检索使用到的Qt库文件，并将其复制到可执行文件所在的目录下。
3.然后执行命令"windeployqt FileArrange.exe --qmldir C:\Qt\Qt5.9.3\5.9.3\msvc2015\qml"。该命令会检索使用到的QML相关库文件到可执行文件所在的目录下。注意，该指令中的C:\Qt\Qt5.9.3\5.9.3\msvc2015\qml是所使用qmake版本的qml库文件目录，需要酌情修改。
*/
import QtQuick                  2.7
import QtQuick.Controls         2.2
import QtQuick.Dialogs          1.2
import WindowsExcelFileAnalyzer 1.0
import GlobalTool               1.0
Item {
    id:root
    anchors.fill: parent
    property var tarPath
    property int mode : 1  //   1.msvc 2. minGW 两种编译器
    property real titleFontSize: 30
    property real subFontSize: 30
    Rectangle{
        anchors.fill: parent
        color: "#1a76d1"
    }
    FileDialog{
        id:fileDialog
        onAccepted: {
            filePath.text=GlobalTool.slipText(fileDialog.fileUrl)
        }
    }
    Column{
        spacing: 10
        Text {
            text: "设置需要打包应用文件:"
            font.pixelSize: titleFontSize
            font.family: fontlist.blackFont.name
            color: "white"
        }
        Row{
            spacing: 10
            TextInput{
                id:filePath
                width: 500
                height: subFontSize
                font.pixelSize: subFontSize*0.8
                color: "white"
                property string placeHoldMessage: ""
                anchors.verticalCenter: parent.verticalCenter
                clip: true
                Rectangle{
                    anchors.fill: parent
                    color: "#00000000"
                    border.color: "white"
                    border.width: 2
                }
            }
            Button{
                width: subFontSize
                height: subFontSize
                text: "浏览"
                onClicked: {
                    fileDialog.open()
                }
            }
        }
    }
}
