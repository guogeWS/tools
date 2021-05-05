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
        property alias path: fileDirectory.text
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
            fileDirectory.text=windowsExcelFileAnalyzer.slipText(fileDialog.fileUrl)+"/"
        }
    }
    Column{
        spacing: 10
        Text {
            text: "请设置素材图片所在目录:"
            font.pixelSize: titleFontSize
            font.family: fontlist.blackFont.name
            color: "white"
        }
        Row{
            spacing: 10
            TextInput{
                id:fileDirectory
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
        Row{
            Text {
                font.pixelSize: subFontSize*0.8
                color: "white"
                text: "起始页码:"
                anchors.verticalCenter: parent.verticalCenter
            }
            Rectangle{
                width: children[0].width+30
                height: titleFontSize
                color: "#00000000"
                border.color: "white"
                border.width: 2
                anchors.verticalCenter: parent.verticalCenter
                TextInput{
                    anchors.centerIn: parent
                    font.pixelSize: subFontSize*0.8
                    color: "white"
                    text: imageStitching.startPage
                    onAccepted: {
                        focus=false
                        imageStitching.startPage=Number(text)
                    }
                    onEditingFinished: {
                        focus=false
                        imageStitching.startPage=Number(text)
                    }
                }
            }
            Item {
                width: 100
                height: subFontSize

            }
            Text {
                font.pixelSize: subFontSize*0.8
                color: "white"
                text: "结束页码:"
                anchors.verticalCenter: parent.verticalCenter
            }

            Rectangle{
                width: children[0].width+30
                height: titleFontSize
                color: "#00000000"
                border.color: "white"
                border.width: 2
                anchors.verticalCenter: parent.verticalCenter
                TextInput{
                    anchors.centerIn: parent
                    font.pixelSize: subFontSize*0.8
                    color: "white"
                    text: imageStitching.endPage
                    onAccepted: {
                        focus=false
                        imageStitching.endPage=Number(text)
                    }
                    onEditingFinished: {
                        focus=false
                        imageStitching.endPage=Number(text)
                    }
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
                imageStitching.imageDir=fileDirectory.text
                imageStitching.startWork()
            }
        }
        Button{
            text: "开始采集"
            onClicked: {
                imageStitching.imageDir=fileDirectory.text
                imageStitching.screenClip()
            }
        }
    }

}
