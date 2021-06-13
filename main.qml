import QtQuick                  2.7
import QtQuick.Controls         2.0
import QtQuick.Layouts          1.3
import FileManager              1.0
import Tools                    1.0
import GlobalTool               1.0
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
    Component.onCompleted: {
        testFunction()
    }
    function testFunction2(){
        var x1=0
        var y1=0
        var x2=400
        var y2=300
        var tarbearing=0;
        var intoAngle=90;
        var speed1=5.0
        var speed2=20.0
        var k=speed2/speed1
        var angle1=tarbearing/180*Math.PI
        var angle2=intoAngle/180*Math.PI
        var a=Math.sin(angle1)+k*Math.sin(angle2);
        var b=Math.cos(angle1)+k*Math.cos(angle2);
        var c=a*a+b*b;
        var d1=Math.sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))
        console.log("d1:"+d1)
        var d2=d1/Math.sqrt(c);
        var x3=x1+d2*Math.cos(angle1)
        var y3=y1+d2*Math.sin(angle1)
        console.log("x3:"+x3+" y3:"+y3)
        var d3=Math.sqrt((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3))
        var t1=d2/speed1
        var t2=d3/speed2
        console.log("t1:"+t1+" t2:"+t2);
    }
    function testFunction(){
        var v1=0;
        var v2=20;
        var x1=0;
        var y1=0;
        var x2=-700;
        var y2=10;
        var ange1=0/180*Math.PI;
        var ange2=30/180*Math.PI;
        var distance=500;
        var k1=x1+distance*Math.cos(ange2)-x2
        var k2=y1+distance*Math.sin(ange2)-y2
        var a=(v1*Math.cos(ange1))*(v1*Math.cos(ange1))+(v1*Math.sin(ange1))*(v1*Math.sin(ange1))-v2*v2
        var b=2*k1*v1*Math.cos(ange1)+1*k2*v1*Math.sin(ange1)+2*distance*v2
        var c=k1*k1+k2*k2-distance*distance
        var t1=(-b+Math.sqrt(b*b-4*a*c))/(2*a)
        var t2=(-b-Math.sqrt(b*b-4*a*c))/(2*a)
        console.log("time 1:"+t1+" time 2:"+t2)
    }
}
