import QtQuick                  2.7
import QtQuick.Controls         2.2
import QtQuick.Dialogs          1.2
import GlobalTool               1.0
import AutoStartSetting         1.0
Item {
    id:root
    property real titleFontSize: 30
    property real subFontSize: 30
    Rectangle{
        anchors.fill: parent
        color: "#1a76d1"
    }
    AutoStartSetting{
        id:autoStartSetting
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
            text: "设置开机自启应用文件:"
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
        Button{
            text: "设置开机自启"
            onClicked: {
                autoStartSetting.filePath=filePath.text
                if(autoStartSetting.creatLink()){
                    showMessage("设置成功")
                }else{
                    showMessage("设置失败")
                }
            }
        }
    }
}
