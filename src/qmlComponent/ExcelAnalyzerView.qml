import QtQuick           2.9
import QtQuick.Controls  2.0
import QtQuick.Dialogs   1.2
import Qt.labs.settings  1.0
import WindowsExcelFileAnalyzer 1.0
Item {
    id:root
    Rectangle{
        anchors.fill: parent
        color: "black"
    }
    WindowsExcelFileAnalyzer{
        id:windowsExcelFileAnalyzer
    }
    Settings{
        id:settings
        property alias path: fileDirectory.text
        property alias year:yearText.text
        property alias mounth:mounthText.text
        property alias day:dayText.text
    }
    Column{
        Text {
            text: "请输入工作日期:"
            font.pixelSize: 50
            color: "white"
        }
        Row{
            TextInput{
                id:yearText
                width: 200
                height: 40
                font.pixelSize: 40
                color: "white"
                property string placeHoldMessage: "2020"
                anchors.verticalCenter: parent.verticalCenter
                Rectangle{
                    anchors.fill: parent
                    color: "#00000000"
                    border.color: "white"
                }
            }
            Text {
                font.pixelSize: 40
                color: "white"
                text: "年"
                anchors.verticalCenter: parent.verticalCenter
            }
            TextInput{
                id:mounthText
                width: 100
                height: 40
                font.pixelSize: 40
                color: "white"
                property string placeHoldMessage: "1"
                Rectangle{
                    anchors.fill: parent
                    color: "#00000000"
                    border.color: "white"
                }
            }
            Text {
                font.pixelSize: 40
                color: "white"
                text: "月"
                anchors.verticalCenter: parent.verticalCenter
            }
            TextInput{
                id:dayText
                width: 100
                height: 40
                font.pixelSize: 40
                color: "white"
                property string placeHoldMessage: "1"
                Rectangle{
                    anchors.fill: parent
                    color: "#00000000"
                    border.color: "white"
                }
            }
            Text {
                font.pixelSize: 40
                color: "white"
                text: "日"
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        Text {

            text: "请设置文件所在目录:"
            font.pixelSize: 50
            color: "white"
        }
        Row{
            TextInput{
                id:fileDirectory
                width: 600
                height: 40
                font.pixelSize: 40
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
                width: 40
                height: 40
                text: "浏览"
                onClicked: {
                    fileDialog.open()
                }
            }
        }
        FileDialog{
            id:fileDialog
            selectFolder:true
            onAccepted: {
                fileDirectory.text=fileDialog.fileUrl
            }
        }
    }
    Button{
        text: "开始"
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            windowsExcelFileAnalyzer.setCurrentData(yearText.text,mounthText.text,dayText.text)
            windowsExcelFileAnalyzer.getUsefulFile(fileDirectory.text)
        }
        /*
        QString currentData="31";
        WindowsExcelFileAnalyzer *excelFileAnalyzer=new WindowsExcelFileAnalyzer();
        excelFileAnalyzer->setCurrentData(currentData);
        QString path=u8"c:/Users/WIN 10/Desktop/工作计划/";
        QDir fileDir(path);
        fileDir.setFilter(QDir::Files);
        QFileInfoList fileInfoList=fileDir.entryInfoList();
        for(int i=0;i<fileInfoList.length();i++){
            QString fileName=fileInfoList.at(i).fileName();
            if(fileName.contains("2020")&&fileName.contains("12")&&fileName.contains(currentData)){
                qDebug()<<"fileName :"<<fileName;
                excelFileAnalyzer->readExcelFile(path+(fileName));
            }
        }
        path=u8"c:/Users/WIN 10/Desktop/工作计划/研发部工作情况-12月.xlsx";
        excelFileAnalyzer->writeExcelFile(path);
        path=u8"c:/Users/WIN 10/Desktop/工作计划/新建文本文档.txt";
        excelFileAnalyzer->outPutToTxtFile(path);
    */
    }
}
