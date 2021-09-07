import QtQuick                  2.7
import QtQuick.Controls         2.0
import QtQuick.Layouts          1.3
import FileManager              1.0
import Tools                    1.0
import GlobalTool               1.0
import Qt.labs.settings         1.0
import QtQuick.Dialogs          1.2
Item{
    id:root
    property real titleFontSize: 30*GlobalTool.getScale()
    property real subFontSize: 30*GlobalTool.getScale()
    Settings{
        id:settings
        property alias homePath : fileDirectory.text
        property var directorList: []
    }
    Rectangle{
        anchors.fill: parent
        color: "#1a76d1"
    }
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
    FileDialog{
        id:fileDialog
        selectFolder:true
        onAccepted: {
            fileDirectory.text=GlobalTool.slipText(fileDialog.fileUrl)+"/"
        }
    }
    Row{
        id:filePath
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
    //文件分组
    Rectangle{
        id:fileTitle
        width: parent.width
        height: fileListbar.height
        color: "#00000000"
        border.color: "white"
        border.width: 2
        anchors.top: filePath.bottom
        TabBar{
            id:fileListbar
            Repeater{
                model: settings.directorList
                TabButton{
                    text: settings.directorList[index].name
                    width:font.pixelSize*6
                    onClicked: {
                    }
                }
            }
            TabButton{
                text: "+"
                width:font.pixelSize*6
                onClicked: {
                    messageBox.editText.connect(getNewGroupName)
                    showEditMessage("输入分组名")
                }
                function getNewGroupName(info){
                    //settings.directorList=[]
                    messageBox.editText.disconnect(getNewGroupName)
                    settings.directorList.push({"name":info,"itemList":[]})
                    settings.directorListChanged()
                    fileManager.makeDir(settings.homePath , info)
                }
            }
        }
    }
    //文件列表
    Rectangle{
        id:fileList
        width: parent.width*0.5
        color: "#00000000"
        border.color: "white"
        border.width: 2
        clip: true
        anchors.bottom: parent.bottom
        anchors.top: fileTitle.bottom
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
                        model: settings.directorList[fileListbar.currentIndex].itemList
                        Item {
                            id: fileGroupItem
                            width: fileList.width
                            height: subFontSize
                            Rectangle{
                                width: parent.width
                                height: 2
                                anchors.bottom: parent.bottom
                            }
                            Column{
                                anchors.centerIn: parent
                                Text {
                                    id: fileGroupName
                                    text: settings.directorList[fileListbar.currentIndex].itemList[index]
                                    color: "white"
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
                    settings.directorList[fileListbar.currentIndex].itemList.push(fileManager.getFileName(drop.urls[0]))
                    settings.directorListChanged()
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
        width: parent.width*0.5
        anchors.top: fileTitle.bottom
        anchors.bottom: fileInfo.top
        anchors.right: parent.right
        color: "#00000000"
        border.color: "white"
        border.width: 2
    }
    //文件备注
    Rectangle{
        id:fileInfo
        width: parent.width*0.5
        height: parent.height*0.5
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
