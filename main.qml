import QtQuick                  2.7
import QtQuick.Controls         2.0
import QtQuick.Layouts          1.3
import FileManager              1.0
import Tools                    1.0
import GlobalTool               1.0
import Qt.labs.settings 1.0
ApplicationWindow {
    id:rootWindow
    visible: true
    width: 640*GlobalTool.getScale()
    height: 600*GlobalTool.getScale()
    title: qsTr("私人工具箱")
    function closeAll(){
        excelAnalyzerView.visible=false
        fileInfoView.visible=false
        imageStitchView.visible=false
        qtApplicationPackage.visible=false
        powerOnAutoStartPage.visible=false
        imageTranslatePage.visible=false
    }
    Settings{
        id:appSettings
        category: "applicationSettings"
        property alias appWidth: rootWindow.width
        property alias appHeight: rootWindow.height
    }
    FontList{
        id:fontlist
    }
    TabBar{
        id:bar
        width: parent.width
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
                powerOnAutoStartPage.visible=true
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
        TabButton{
            text: "窗口翻译"
            onClicked: {
                closeAll()
                imageTranslatePage.visible=true
            }
        }
    }
    Item {
        id:containItem
        width: parent.width
        anchors.top: bar.bottom
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
        PowerOnAutoStartPage{
            id:powerOnAutoStartPage
            anchors.fill:parent
            visible:false
        }
        ImageTranslate{
            id:imageTranslatePage
            anchors.fill:parent
            visible:false
        }
    }
    Rectangle{
        id:messageBox
        width: ( editable ? message_edit.width : message.width ) + parent.width*0.1
        height: parent.height*0.1
        anchors.centerIn: parent
        color: "#99FFFFFF"
        radius: height*0.4
        visible: false
        property bool editable: false
        signal editText(var info)
        Text {
            id: message
            color: "black"
            text: "测试"
            anchors.centerIn: parent
            font.pixelSize: parent.height*0.6
            font.family: fontlist.blackFont.name
            font.bold: true
            visible: !parent.editable
        }
        TextInput{
            id: message_edit
            color: "black"
            text: "测试"
            anchors.centerIn: parent
            font.pixelSize: parent.height*0.6
            font.family: fontlist.blackFont.name
            font.bold: true
            visible: parent.editable
            onAccepted: {
                messageBox.visible=false
                parent.editText(message_edit.text)
            }
        }
    }
    Timer{
        id:messageBoxHideTimer
        interval: 3000
        repeat: false
        running: false
        onTriggered: {
            messageBox.visible=false
        }
    }
    function showMessage(info){
        messageBox.editable=false
        message.text=info
        messageBox.visible=true
        messageBoxHideTimer.restart()
    }
    function showEditMessage(info){
        messageBox.editable=true
        message_edit.text=info
        messageBox.visible=true
    }
    Component.onCompleted: {
        /**/
        var groupName = "RCINInfo"
        var propertyList = ["ch1in","ch2in","ch3in","ch4in","ch5in","ch6in","ch7in","ch8in","ch9in","ch10in","ch11in","ch12in","ch13in","ch14in","rssi"]
        var nameList = ["输入通道1","输入通道2","输入通道3","输入通道4","输入通道5","输入通道6","输入通道7","输入通道8","输入通道9","输入通道10","输入通道11","输入通道12","输入通道13","输入通道14","通信强度"]
        var typeList = ["uint16","uint16","uint16","uint16","uint16","uint16","uint16","uint16","uint16","uint16","uint16","uint16","uint16","uint16",'uint8']
        var fixNumList = ["0","0","0","0","0","0","0","0","0","0","0","0","0","0","0"]
        var unitList = ["us","us","us","us","us","us","us","us","us","us","us","us","us","us",""]
        //autoBuildCode(groupName,propertyList,nameList,typeList,fixNumList,unitList)
    }

    function autoBuildCode(groupName,propertyNameList,humannameList,typeList,fixNumList,unitList){
        var codeList = ""
        codeList += "class " +"Vehicle"+groupName+"FactGroup"+":public FactGroup{\r\n"
        codeList += "Q_OBJECT\r\n"
        codeList += "public:\r\n"
        codeList += "Vehicle"+groupName+"FactGroup(QObject* parent = NULL);\r\n"
        for(var i=0;i<propertyNameList.length;i++)
            codeList += "Q_PROPERTY(Fact* "+propertyNameList[i]+"Fact"+"        READ "+propertyNameList[i]+"Fact"+"        CONSTANT)\r\n"
        for(var i=0;i<propertyNameList.length;i++)
            codeList += "Fact* "+propertyNameList[i]+"Fact"+" (void) { return &_"+propertyNameList[i]+"Fact"+"; }\r\n"
        codeList += "static const char* _settingsGroup;\r\n"
        codeList += "private:\r\n"
        for(var i=0;i<propertyNameList.length;i++)
            codeList += "Fact                "+"_"+propertyNameList[i]+"Fact;\r\n"
        codeList +="};\r\n"
        console.info(codeList)
        codeList = ""
        codeList += "Vehicle"+groupName+"FactGroup"+"::"+"Vehicle"+groupName+"FactGroup(QObject* parent)\r\n"
        codeList += ":FactGroup(1000,\":/json/Vehicle/"+groupName+".json"+"\",parent)\r\n"
        for(var i=0;i<propertyNameList.length;i++){
            var type =""
            switch(typeList[i]){
            case "uint8":
                type="valueTypeUint8"
                break;
            case "int8":
                type="valueTypeInt8"
                break;
            case "uint16":
                type="valueTypeUint16"
                break;
            case "int16":
                type="valueTypeInt16"
                break;
            case "uint32":
                type="valueTypeUint32"
                break;
            case "int32":
                type="valueTypeInt32"
                break;
            case "float":
                type="valueTypeFloat"
                break;
            case "double":
                type="valueTypeDouble"
                break;
            }
            codeList += ",_"+propertyNameList[i]+"Fact"+"              (0,u8\""+humannameList[i]+"\",                 FactMetaData::"+type+")\r\n"
        }

        codeList += "{\r\n"
        for(var i=0;i<propertyNameList.length;i++)
            codeList += "_addFact(&_"+propertyNameList[i]+"Fact"+",u8\""+humannameList[i]+"\");\r\n"
        codeList += "}\r\n"
        console.info(codeList)
        codeList = ""
        codeList +="[\r\n"
        for(var i=0;i<propertyNameList.length;i++){
            codeList += "{\r\n"
            codeList +="\"name\":                \""+humannameList[i]+"\",\r\n"
            codeList +="\"shortDescription\":    \""+humannameList[i]+"\",\r\n"
            codeList +="\"type\":                \""+typeList[i]+"\",\r\n"
            codeList +="\"decimalPlaces\":       "+fixNumList[i]+",\r\n"
            codeList +="\"units\":               \""+unitList[i]+"\"\r\n"
            if(i==propertyNameList.length-1){
                codeList += "}\r\n"
            }else{
                codeList += "},\r\n"
            }

        }
        codeList +="]\r\n"
        console.log(codeList)
    }
}
