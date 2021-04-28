﻿import QtQuick                  2.7
import QtQuick.Controls         2.0
import QtQuick.Layouts          1.3
import FileManager              1.0
import Tools                    1.0
Item{
    id:root
    Component{
        id:fileGroupItemComponent
        QtObject{
            property var groupName: "未定义组"
            property var directorPath:":/files/undefinedGroup"//文件夹路径
            property var modelNameList: []  //文件名称列表
        }
    }
    FileManager{
        id:fileManager
    }
    Rectangle{
        anchors.fill: parent
        color: "black"
        visible: true
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
            property var modelGroupList: []

            //将文件托拽到此处 读取文件路径
            Flickable{
                anchors.fill: parent
                contentHeight: fileGroupList.height
                contentWidth: fileGroupList.width
                flickableDirection: Flickable.VerticalFlick
                //根据文件路径获取文件名
                function getFileNameFromPath(){
                }
                Item {
                    id: fileGroupList
                    Column{
                        Repeater{
                            model: 1
                            Item {
                                id: fileGroupItem
                                Column{
                                    Text {
                                        id: fileGroupName
                                        text: "未定义分组"
                                        color: "white"
                                    }
                                    Item {
                                        id: fileNameList
                                        width: childrenRect.width
                                        height: childrenRect.height
                                        Rectangle{
                                            anchors.fill: parent
                                            color: "#33FFFFFF"
                                        }
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
}
