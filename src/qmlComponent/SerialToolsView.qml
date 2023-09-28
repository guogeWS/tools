import QtQuick              2.7
import SerialTools          1.0
import QtQuick.Controls     2.2
import Qt.labs.settings     1.0
Item {
    id:root
    property real titleFontSize: 30
    property real subFontSize: 30
    property var  serialTool: serialTools
    property var  tcpTool
    Settings{
        id:settings
    }
    Rectangle{
        anchors.fill: parent
        color: "#1a76d1"
    }
    SerialTools{
        id:serialTools
        onMessageReceived: {
            tcpTool.sendMessage(message)
        }
    }
    Column{
        anchors.fill: parent
        spacing: 10
        Row{
            Text {
                font.pixelSize: subFontSize*0.8
                font.family: fontlist.blackFont.name
                color: "white"
                text: "名称:"
                anchors.verticalCenter: parent.verticalCenter
            }
            TextInput{
                id:name
                width: 200
                height: subFontSize
                font.pixelSize: subFontSize*0.8
                color: "white"
                anchors.verticalCenter: parent.verticalCenter
                Rectangle{
                    anchors.fill: parent
                    color: "#00000000"
                    border.color: "white"
                }
                onFocusChanged: {
                    if(!focus){
                        settings.ipAddress = text
                    }
                }
            }
            Text {
                font.pixelSize: subFontSize*0.8
                font.family: fontlist.blackFont.name
                color: "white"
                text: "波特率:"
                anchors.verticalCenter: parent.verticalCenter
            }
            TextInput{
                id:baudrate
                width: 200
                height: subFontSize
                font.pixelSize: subFontSize*0.8
                color: "white"
                anchors.verticalCenter: parent.verticalCenter
                Rectangle{
                    anchors.fill: parent
                    color: "#00000000"
                    border.color: "white"
                }
                onFocusChanged: {
                    if(!focus){
                        settings.socketPort = text
                    }
                }
            }
            Button{
                text: "连接"
                onClicked: {
                    serialTools.openSerial()
                }
            }
            Button{
                text: "断开"
                onClicked: {

                }
            }
        }
    }
}
