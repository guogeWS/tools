import QtQuick              2.7
import TcpTools             1.0
import QtQuick.Controls     2.2
import Qt.labs.settings     1.0
Item {
    id:root
    property real titleFontSize: 30
    property real subFontSize: 30
    property var  tcpTool: tcpTools
    property var  serialTool
    Settings{
        id:settings
        property var ipAddress:""
        property var socketPort:""
    }
    Rectangle{
        anchors.fill: parent
        color: "#1a76d1"
    }
    TcpTools{
        id:tcpTools
        onMessageReceived: {
            serialTool.sendMessage(message)
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
                text: "IP地址:"
                anchors.verticalCenter: parent.verticalCenter
            }
            TextInput{
                id:ip
                width: 200
                height: subFontSize
                font.pixelSize: subFontSize*0.8
                color: "white"
                text:settings.ipAddress
                property string placeHoldMessage: "2020"
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
                text: "端口号:"
                anchors.verticalCenter: parent.verticalCenter
            }
            TextInput{
                id:port
                width: 200
                height: subFontSize
                font.pixelSize: subFontSize*0.8
                color: "white"
                text: settings.socketPort
                property string placeHoldMessage: "2020"
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
                    tcpTools.ipAddress = ip.text
                    tcpTools.socketPort = Number(port.text)
                    tcpTools.connectToServer()
                }
            }
            Button{
                text: "断开"
                onClicked: {
                    tcpTools.ipAddress = ip.text
                    tcpTools.socketPort = Number(port.text)
                    tcpTools.connectToServer()
                }
            }
        }
        Rectangle{
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width*0.8
            height: parent.height*0.4
            color: "#00000000"
            border.color: "white"
            border.width: 2
            Text {
                id:receiveMessageArea
                anchors.fill: parent
                font.pixelSize: subFontSize*0.8
                font.family: fontlist.blackFont.name
                wrapMode: Text.Wrap
                Connections{
                    target: tcpTools
                    onMessageReceivedChanged:{
                        receiveMessageArea.text+=tcpTools.messageReceived
                    }
                }
            }
        }
        Row{
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            Button{
                text: "清空"
                onClicked: {
                    receiveMessageArea.text=""
                }
            }
            CheckBox{
                text: "HEX"
            }
            Text {
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: subFontSize*0.8
                font.family: fontlist.blackFont.name
                text: receiveMessageArea.text.length
            }
        }
        Rectangle{
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width*0.8
            height: parent.height*0.4
            color: "#00000000"
            border.color: "white"
            border.width: 2
            TextArea{
                id:sendMessageArea
                anchors.fill: parent
                text: "测试"
                font.pixelSize: subFontSize*0.8
                font.family: fontlist.blackFont.name
            }
        }
        Row{
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            Button{
                text: "清空"
                onClicked: {
                    sendMessageArea.text=""
                }
            }
            Button{
                text: "发送"
                onClicked: {
                    tcpTools.sendMessage(sendMessageArea.text)
                }
            }
            CheckBox{
                text: "HEX"
            }
            Text {
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: subFontSize*0.8
                font.family: fontlist.blackFont.name
                text: sendMessageArea.text.length
            }
        }
    }
}
