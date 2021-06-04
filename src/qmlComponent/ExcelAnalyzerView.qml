import QtQuick           2.9
import QtQuick.Controls  2.2
import QtQuick.Dialogs   1.2
import Qt.labs.settings  1.0
import WindowsExcelFileAnalyzer 1.0
import Tools             1.0
import GlobalTool        1.0
Item {
    id:root
    property real titleFontSize: 30*GlobalTool.getScale()
    property real subFontSize: 30*GlobalTool.getScale()
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
        property alias year: yearText.text
        property alias mounth:mounthText.text
        property alias day:dayText.text
        property alias saveType: windowsExcelFileAnalyzer.analyzeType
        property alias nameCount: windowsExcelFileAnalyzer.nameNumQML
        property alias nameColumn: windowsExcelFileAnalyzer.nameLineCountQML
        property alias workIndex: windowsExcelFileAnalyzer.workIndex
        property alias tomIndex: windowsExcelFileAnalyzer.tommIndex
        property alias dataCount: windowsExcelFileAnalyzer.dataLineCountQML
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
                width: root.width*0.7
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
                width: root.width*0.7
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
                text: "..."
                font.pixelSize: height*0.7
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
        Row{
            spacing: 20
            Text {
                font.pixelSize: subFontSize*0.8
                font.family: fontlist.blackFont.name
                color: "white"
                text: "日期所在行号:"
                anchors.verticalCenter: parent.verticalCenter
            }
            TextInput{
                width: 50
                height: subFontSize
                font.pixelSize: subFontSize*0.8
                color: "white"
                text: settings.dataCount
                onAccepted: {
                    settings.dataCount=text
                    focus=false
                }
                Rectangle{
                    anchors.fill: parent
                    color: "#00000000"
                    border.color: "white"
                }
            }
        }
        Row{
            spacing: 20
            Text {
                font.pixelSize: subFontSize*0.8
                font.family: fontlist.blackFont.name
                color: "white"
                text: "姓名数量:"
                anchors.verticalCenter: parent.verticalCenter
            }
            TextInput{
                width: 50
                height: subFontSize
                font.pixelSize: subFontSize*0.8
                color: "white"
                text: settings.nameCount
                onAccepted: {
                    settings.nameCount=text
                    focus=false
                }
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
                text: "姓名所在列号:"
                anchors.verticalCenter: parent.verticalCenter
            }
            TextInput{
                width: 50
                height: subFontSize
                font.pixelSize: subFontSize*0.8
                color: "white"
                text: settings.nameColumn
                onAccepted: {
                    settings.nameColumn=text
                    focus=false
                }
                Rectangle{
                    anchors.fill: parent
                    color: "#00000000"
                    border.color: "white"
                }
            }
        }
        Row{
            spacing: 20
            Text {
                font.pixelSize: subFontSize*0.8
                font.family: fontlist.blackFont.name
                color: "white"
                text: "总结所在行号:"
                anchors.verticalCenter: parent.verticalCenter
            }
            TextInput{
                width: 50
                height: subFontSize
                font.pixelSize: subFontSize*0.8
                color: "white"
                text: settings.workIndex
                onAccepted: {
                    settings.workIndex=text
                    focus=false
                }
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
                text: "计划所在行号:"
                anchors.verticalCenter: parent.verticalCenter
            }
            TextInput{
                width: 50
                height: subFontSize
                font.pixelSize: subFontSize*0.8
                color: "white"
                text: settings.tomIndex
                onAccepted: {
                    settings.tomIndex=text
                    focus=false
                }
                Rectangle{
                    anchors.fill: parent
                    color: "#00000000"
                    border.color: "white"
                }
            }
        }
        Rectangle{
            width: 550*GlobalTool.getScale()
            height: 150*GlobalTool.getScale()
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
