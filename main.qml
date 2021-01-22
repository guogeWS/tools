import QtQuick                  2.7
import QtQuick.Controls         2.0
import QtQuick.Layouts          1.3
import FileManager              1.0
import Tools                    1.0
ApplicationWindow {
    id:rootWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("文件整理助手")
    property var toolNameList: ["每日计划整理工具","串口转TCP工具"]
    Grid{
        anchors.fill: parent
        Repeater{
            Item {
                width: rootWindow.width/4
                height: width
                Rectangle{
                }
            }
        }
    }
    FileManager{
        id:fileManager
    }
    Rectangle{
        anchors.fill: parent
        color: "black"
        visible: false
        //文件列表
        Rectangle{
            id:fileList
            width: parent.width*0.45
            height: parent.height*0.9
            anchors.verticalCenter: parent.verticalCenter
            color: "#00000000"
            border.color: "white"
            border.width: 2
            clip: true
            property var modelNameList: []
            //将文件托拽到此处 读取文件路径
            Flickable{
                anchors.fill: parent
                contentHeight: fileNameList.height
                contentWidth: fileNameList.width
                flickableDirection: Flickable.VerticalFlick
                //根据文件路径获取文件名
                function getFileNameFromPath(){
                }
                Item {
                    id: fileNameList
                    Column{
                        Repeater{
                            model: fileList.modelNameList
                            Item {
                                width: fileList.width
                                height: fileList.height*0.1
                                Rectangle{
                                    width: parent.width
                                    height: parent.height*0.9
                                    anchors.centerIn: parent
                                    Text {
                                        anchors.verticalCenter: parent.verticalCenter
                                        color: "black"
                                        font.pixelSize: parent.height*0.9
                                        text: fileList.modelNameList[index]
                                    }
                                }
                            }
                        }
                    }
                }
            }
            DropArea{
                anchors.fill: parent
                onDropped: {
                    if(drop.hasUrls){
                        fileList.modelNameList.push(fileManager.getFileName(drop.urls[0]))
                        fileList.modelNameListChanged()
                        for(var i = 0; i < drop.urls.length; i++){
                            console.log(drop.urls.length);
                            console.log(drop.urls[i]);
                            console.log("keys"+drop.keys)
                            console.log("formats"+drop.formats)
                        }
                    }
                }
            }
        }
        //文件截图
        Rectangle{
            id:fileImage
            width: parent.width*0.45
            height: parent.height*0.45
            anchors.right: parent.right
            color: "#00000000"
            border.color: "white"
            border.width: 2
        }
        //文件备注
        Rectangle{
            id:fileInfo
            width: parent.width*0.45
            height: parent.height*0.45
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            color: "#00000000"
            border.color: "white"
            border.width: 2
            TextArea{
                anchors.fill: parent
                text: "文件备注：\n"
                color: "white"
            }
        }
    }
    ExcelAnalyzerView{
        id:excelAnalyzerView
        anchors.fill:parent
    }
}
