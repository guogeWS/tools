import QtQuick                  2.7
import QtQuick.Controls         2.0
import QtQuick.Layouts          1.3
import FileManager              1.0
import Tools                    1.0
import GlobalTool               1.0
ApplicationWindow {
    id:rootWindow
    visible: true
    width: 640/GlobalTool.getScale()
    height: 600/GlobalTool.getScale()
    title: qsTr("私人工具箱")
    function closeAll(){
        excelAnalyzerView.visible=false
        fileInfoView.visible=false
        imageStitchView.visible=false
        qtApplicationPackage.visible=false
    }
    FontList{
        id:fontlist
    }
    TabBar{
        id:bar
        width: parent.width
        height: parent.height*0.1
        TabButton{
            text:"工作计划整理工具"
            onClicked: {
                closeAll()
                excelAnalyzerView.visible=true
            }
        }
        TabButton{
            text: "文件整理工具"
            onClicked: {
                closeAll()
                fileInfoView.visible=true
            }
        }
        TabButton{
            text: "ucg杂志图片整合"
            onClicked: {
                closeAll()
                imageStitchView.visible=true
            }
        }
        TabButton{
            text: "QT应用打包"
            onClicked: {
                closeAll()
                qtApplicationPackage.visible=true
            }
        }
        TabButton{
            text: "快速设置开机自启"
            onClicked: {
                closeAll()
            }
        }
        TabButton{
            text: "串口助手"
            onClicked: {
                closeAll()
            }
        }
        TabButton{
            text: "网络助手"
            onClicked: {
                closeAll()
            }
        }
    }
    Item {
        id:containItem
        width: parent.width
        height: parent.height*0.93
        anchors.bottom: parent.bottom
        ExcelAnalyzerView{
            id:excelAnalyzerView
            anchors.fill:parent
            visible:true
        }
        FileInfoView{
            id:fileInfoView
            anchors.fill:parent
            visible:false
        }
        ImageStitchView{
            id:imageStitchView
            anchors.fill:parent
            visible:false
        }
        QtApplicationPackage{
            id:qtApplicationPackage
            anchors.fill:parent
            visible:false
        }
    }

}
