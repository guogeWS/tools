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
    property var orcText:"abc"
    MainFunction{
        id:mainFunction
        targetX: subWindow.x
        targetY: subWindow.y
        targetWidth: subWindow.width
        targetHeight: subWindow.height
        grabEnable: root.visible
    }
    Window{
        id:subWindow
        width: 300
        height: 100
        color: "#00000000"
        visible: root.visible
        flags: Qt.Window | Qt.FramelessWindowHint
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
