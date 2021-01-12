import QtQuick           2.9
import QtQuick.Controls  2.2
import QtQuick.Dialogs   1.2
import Qt.labs.settings  1.0
import WindowsExcelFileAnalyzer 1.0
import Tools             1.0
Item {
    id:root
    property real titleFontSize: 30
    property real subFontSize: 30
    Rectangle{
        anchors.fill: parent
        color: "#1a76d1"
    }
    FontList{
        id:fontlist
    }
    WindowsExcelFileAnalyzer{
        id:windowsExcelFileAnalyzer
    }
    Settings{
        id:settings
        property alias path: fileDirectory.text
        property alias file: filePath.text
        property alias year:yearText.text
        property alias mounth:mounthText.text
        property alias day:dayText.text
    }
    Column{
        spacing: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10

        Text {
            text: "请输入工作日期:"
            font.pixelSize: titleFontSize
            font.family: fontlist.blackFont.name
            color: "white"
        }
        Row{
            TextInput{
                id:yearText
                width: 200
                height: subFontSize
                font.pixelSize: subFontSize*0.8
                color: "white"
                text: settings.year
                property string placeHoldMessage: "2020"
                anchors.verticalCenter: parent.verticalCenter
                Rectangle{
                    anchors.fill: parent
                    color: "#00000000"
                    border.color: "white"
                }
            }
            Text {
                font.pixelSize: subFontSize*0.8
                font.family: fontlist.blackFont.name
                color: "white"
                text: "年"
                anchors.verticalCenter: parent.verticalCenter
            }
            TextInput{
                id:mounthText
                width: 100
                height: subFontSize
                font.pixelSize: subFontSize*0.8
                color: "white"
                property string placeHoldMessage: "1"
                Rectangle{
                    anchors.fill: parent
                    color: "#00000000"
                    border.color: "white"
                }
            }
            Text {
                font.pixelSize: subFontSize*0.8
                font.family: fontlist.blackFont.name
                color: "white"
                text: "月"
                anchors.verticalCenter: parent.verticalCenter
            }
            TextInput{
                id:dayText
                width: 100
                height: subFontSize
                font.pixelSize: subFontSize*0.8
                color: "white"
                property string placeHoldMessage: "1"
                Rectangle{
                    anchors.fill: parent
                    color: "#00000000"
                    border.color: "white"
                }
            }
            Text {
                font.pixelSize: subFontSize*0.8
                font.family: fontlist.blackFont.name
                color: "white"
                text: "日"
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        Text {
            text: "请设置文件所在目录:"
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
        Text {
            text: "请设置输出文件:"
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
                }
            }
            Button{
                width: subFontSize
                height: subFontSize
                text: "浏览"
                onClicked: {
                    fileDialog2.open()
                }
            }
        }
        FileDialog{
            id:fileDialog
            selectFolder:true
            onAccepted: {
                fileDirectory.text=windowsExcelFileAnalyzer.slipText(fileDialog.fileUrl)+"/"
            }
        }
        FileDialog{
            id:fileDialog2
            onAccepted: {
                filePath.text=windowsExcelFileAnalyzer.slipText(fileDialog2.fileUrl)
            }
        }
        Rectangle{
            width: 550
            height: 150
            color: "#00000000"
            border.color: "white"
            border.width: 2
            clip: true
            ScrollView{
                anchors.fill: parent
                TextArea{
                    id:outputMessageArea
                    font.pixelSize: 20
                    font.family: fontlist.blackFont.name
                    color: "black"
                    selectByKeyboard: true
                    selectByMouse: true
                }
            }
        }

    }
    Button{
        text: "开始"
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            windowsExcelFileAnalyzer.setTargetFile(windowsExcelFileAnalyzer.slipText(filePath.text))
            windowsExcelFileAnalyzer.setCurrentData(yearText.text,mounthText.text,dayText.text)
            windowsExcelFileAnalyzer.getUsefulFile(fileDirectory.text)
            outputMessageArea.text=windowsExcelFileAnalyzer.outPutToTxtFile("")
        }
    }
}
