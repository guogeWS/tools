import QtQuick 2.7
import QtQuick.Controls  2.2
import QtQuick.Dialogs   1.2
import Qt.labs.settings  1.0
import WindowsExcelFileAnalyzer 1.0
import ImageStitching    1.0
Item {
    property real titleFontSize: 30
    property real subFontSize: 30
    Rectangle{
        anchors.fill: parent
        color: "#1a76d1"
    }
    FontList{
        id:fontlist
    }
    Settings{
        id:settings
        property alias path: fileDirectory2.text
    }
    WindowsExcelFileAnalyzer{
        id:windowsExcelFileAnalyzer
    }
    ImageStitching{
        id:imageStitching
    }
    FileDialog{
        id:fileDialog
        selectFolder:true
        onAccepted: {
            fileDirectory2.text=windowsExcelFileAnalyzer.slipText(fileDialog.fileUrl)+"/"
        }
    }
    Column{
        Text {
            text: "请设置素材图片所在目录:"
            font.pixelSize: titleFontSize
            font.family: fontlist.blackFont.name
            color: "white"
        }
        Row{
            spacing: 10
            TextInput{
                id:fileDirectory2
                width: 500
                height: subFontSize
                font.pixelSize: subFontSize*0.8
                color: "white"
                property string placeHoldMessage: ""
                anchors.verticalCenter: parent.verticalCenter
                Rectangle{
                    anchors.fill: parent
                    color: "#00000000"
                    border.color: "white"
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
    Row{
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: parent.width*0.1
        Button{
            text: "开始合成"
            onClicked: {
                imageStitching.imageDir=fileDirectory2.text
                imageStitching.startWork()
            }
        }
        Button{
            text: "开始采集"
            onClicked: {
                imageStitching.imageDir=fileDirectory2.text
                imageStitching.screenClip()
            }
        }
    }

}
