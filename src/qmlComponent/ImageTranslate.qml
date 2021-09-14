import QtQuick                  2.7
import QtQuick.Controls         2.0
import QtQuick.Layouts          1.3
import MainFunction             1.0
import Tools                    1.0
import GlobalTool               1.0
import Qt.labs.settings         1.0
import QtQuick.Dialogs          1.2
import QtQuick.Window           2.2
Item{
    id:root
    property real titleFontSize: 30*GlobalTool.getScale()
    property real subFontSize: 30*GlobalTool.getScale()
    property var imageItem
    onVisibleChanged: {
//        if(visible){
//            mainFunction.startFunction()
//        }else{
//            mainFunction.closeFunction()
//        }
    }
    Settings{
        id:settings
        property string ipAddress1:"0"
        property string ipAddress2:"0"
        property string ipAddress3:"0"
        property string ipAddress4:"0"
    }
    Rectangle{
        anchors.fill: parent
        color: "#1a76d1"
    }
    Column{
        spacing: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        Text {
            text: "请输入服务器IP:"
            font.pixelSize: titleFontSize
            font.family: fontlist.blackFont.name
            color: "white"
        }
        Row{
            TextInput{
                width: 50
                height: subFontSize
                font.pixelSize: subFontSize*0.8
                color: "white"
                text: settings.ipAddress1
                anchors.verticalCenter: parent.verticalCenter
                validator: IntValidator{bottom: 0; top: 999;}
                Rectangle{
                    anchors.fill: parent
                    color: "#00000000"
                    border.color: "white"
                }
                onAccepted: {
                    settings.ipAddress1=text
                    focus=false
                }
            }
            Text {
                text: "."
                height: subFontSize
                font.pixelSize: subFontSize*0.8
                color: "white"
            }
            TextInput{
                width: 50
                height: subFontSize
                font.pixelSize: subFontSize*0.8
                color: "white"
                text: settings.ipAddress2
                anchors.verticalCenter: parent.verticalCenter
                validator: IntValidator{bottom: 0; top: 999;}
                Rectangle{
                    anchors.fill: parent
                    color: "#00000000"
                    border.color: "white"
                }
                onAccepted: {
                    settings.ipAddress2=text
                    focus=false
                }
            }
            Text {
                text: "."
                height: subFontSize
                font.pixelSize: subFontSize*0.8
                color: "white"
            }
            TextInput{
                width: 50
                height: subFontSize
                font.pixelSize: subFontSize*0.8
                color: "white"
                text: settings.ipAddress3
                anchors.verticalCenter: parent.verticalCenter
                validator: IntValidator{bottom: 0; top: 999;}
                Rectangle{
                    anchors.fill: parent
                    color: "#00000000"
                    border.color: "white"
                }
                onAccepted: {
                    settings.ipAddress3=text
                    focus=false
                }
            }
            Text {
                text: "."
                height: subFontSize
                font.pixelSize: subFontSize*0.8
                color: "white"
            }
            TextInput{
                width: 50
                height: subFontSize
                font.pixelSize: subFontSize*0.8
                color: "white"
                text: settings.ipAddress4
                anchors.verticalCenter: parent.verticalCenter
                validator: IntValidator{bottom: 0; top: 999;}
                Rectangle{
                    anchors.fill: parent
                    color: "#00000000"
                    border.color: "white"
                }
                onAccepted: {
                    settings.ipAddress4=text
                    focus=false
                }
            }
        }
        Row{
            spacing: 40
            Button{
                width: 60
                text: "开始"
                onClicked: {
                    mainFunction.startFunction()
                }
            }
            Button{
                width: 60
                text: "停止"
                onClicked: {
                    mainFunction.closeFunction()
                }
            }
            Button{
                width: 60
                text: "切换显示"
                onClicked: {
                    mainFunction.closeFunction()
                }
            }
        }
    }
//    Text {
//        width: parent.width
//        text: mainFunction.analyzeText
//        font.pixelSize: titleFontSize
//        font.family: fontlist.blackFont.name
//        color: "white"
//        wrapMode:Text.WordWrap
//    }
    MainFunction{
        id:mainFunction
        targetX: subWindow.x
        targetY: subWindow.y
        targetWidth: subWindow.width
        targetHeight: subWindow.height
        grabEnable: root.visible
        ipAddress: settings.ipAddress1+"."+settings.ipAddress2+"."+settings.ipAddress3+"."+settings.ipAddress4
    }
    Window{
        id:subWindow
        width: 300
        height: 100
        color: "#00000000"
        visible: root.visible
        flags: Qt.FramelessWindowHint
        Rectangle{
            anchors.fill: parent
            color: "#00000000"
            border.color: "black"
            border.width: 4
        }
        MouseArea{
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton //只处理鼠标左键
            property point clickPos: "0,0"
            onPressed: { //接收鼠标按下事件
                clickPos  = Qt.point(mouse.x,mouse.y)
            }
            onPositionChanged: { //鼠标按下后改变位置
                //鼠标偏移量
                var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
                subWindow.setX(subWindow.x+delta.x)
                subWindow.setY(subWindow.y+delta.y)
            }
        }
    }
}
