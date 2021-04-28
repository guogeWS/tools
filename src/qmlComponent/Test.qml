import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Extras 1.4
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.4
/*
Rectangle {
    id: root
    width: 500
    height: 500//60*pathView.model
    color: "black";
    Component {
        id: rectDelegate;
        Rectangle{
            color: "red"
            width: 100
            height: 50
            Text {
                id: name
                text:index
            }
        }
    }

    PathView {
        id: pathView;
        x: 38
        width: 424
        height: root.height
        clip: true
        anchors.horizontalCenter: parent.horizontalCenter
//        anchors.verticalCenterOffset: 1
        anchors.verticalCenter: parent.verticalCenter
//      interactive :true
//        offset :0.1
        model: 30
        pathItemCount: 3
        preferredHighlightBegin: 0.5;
        preferredHighlightEnd: 0.5;
//        highlightRangeMode: PathView.NoHighlightRange
//        maximumFlickVelocity: 1000
        delegate: rectDelegate;
        path: pathVertical
        Path {
            id:pathVertical
            property int height: root.height
            startX: width/2
            startY: 0
            PathAttribute { name: "t_scale"; value: 0.5}
            PathAttribute { name: "itemZ"; value: 0}
            PathLine { x: pathVertical.startX; y: height*0.5}

            PathAttribute { name: "t_scale"; value: 0.5}
            PathAttribute { name: "itemZ"; value: 1}
            PathLine { x: pathVertical.startX; y: height}

        }
        focus: true
//        Keys.onLeftPressed: decrementCurrentIndex();
//        Keys.onRightPressed: incrementCurrentIndex();
    }
}*/
/*
Tumbler {
    id:column_airlist
    x: 3
    y: 49
    width: 150
    height: 867
    anchors.horizontalCenter: parent.horizontalCenter//863//*visibleItemCount/9

    TumblerColumn{
        model: 4
        width: 132
    }
    style: TumblerStyle{
        visibleItemCount: 5
        frame : Rectangle{
            // implicitWidth : 2
            color: "green"
            opacity: 0.6
        }
        background:  Rectangle{
            color: "yellow"
        }
        foreground: Rectangle{
            color: "black"
            opacity: 0.3
            gradient: Gradient {
                GradientStop { position: 0.2; color: "lightsteelblue" }
                GradientStop { position: 0.5; color: "blue" }
                GradientStop { position: 0.8; color: "lightsteelblue" }
            }
        }
        delegate:

            Rectangle{
            id:pp
            width: 130
            height: 50
            color: "red"
            border.color: "aqua"

        }

    }
}
Rectangle {
    id: root
    width: 500
    height: itemCount*buttonItemHeight+columnSpacing*(itemCount-1) //60*pathView.model
    color: "black"
    clip: true
    property real  itemCount: calculationItemCount() //(modelList%2==0?modelList-1:modelList)>9?9:(modelList%2==0?modelList-1:modelList)
    property var   modelList: 200
    property real  columnSpacing: column_airlist.spacing
    property real  buttonItemHeight: 50
    property bool  flickavailable: modelList>=3
    anchors.verticalCenter: parent.verticalCenter
    onModelListChanged: {
    }
    function calculationItemCount(){
        if(modelList<3){
            itemCount=modelList
        }else if(modelList>=9){
            itemCount=9
        }else{
            itemCount=modelList%2==0?modelList-1:modelList
        }
    }
    Column{
        id:column_airlist
        width: 132
        spacing: 10
        property real tempY: 0
        y:tempY>0?tempY-(column_airlist.height*1-buttonItemHeight*itemCount*2-columnSpacing*(itemCount*2-1))
                 :(tempY<-(column_airlist.height-root.height)?tempY+buttonItemHeight*modelList+columnSpacing*modelList:tempY)
        Repeater{
            model: modelList+itemCount*2
            Rectangle{
                id:item
                width: 100
                height: 50
                color: "red"
                Text {
                    anchors.centerIn: parent
                    color: "white"
                    text: (index+modelList-itemCount)%modelList
                    font.pixelSize: parent.height*0.5
                }
                function releaseFunction(){}
                MouseArea{
                    id:mou
                    anchors.fill: parent
                    hoverEnabled: true
                    function pressFunction(){}
                    function releaseFunction(){if(containsMouse){console.log(index)}}
                    Component.onCompleted: {
                        flickMouse.press_.connect(mou.pressFunction)
                        flickMouse.release_.connect(mou.releaseFunction)
                    }
                }
            }
        }
    }

    NumberAnimation {
        id:flickAnimation
        target: column_airlist
        property: "tempY"
        duration: 600
        easing.type:Easing.OutQuart//Easing.OutQuad
    }
    Timer{
        id:flickSpeedTimer
        interval: 50
        repeat: true
        property real lastY: 0
        property real speed: 0
        onTriggered: {
            speed=flickMouse.mouseY-lastY
            lastY=flickMouse.mouseY
        }
    }
    MouseArea{
        id:flickMouse
        anchors.fill: parent
        property real pressX: 0
        property real pressY: 0
        property real lastYPosition: 0
        property bool draging: false
        property bool moved: false
        function flickingDelay(toValue){
            flickAnimation.to=toValue
            flickAnimation.start()
        }
        function startFlicking(){
            flickSpeedTimer.lastY=mouseY
            flickSpeedTimer.speed=0
            flickSpeedTimer.start()
        }
        signal press_()
        signal release_()
        onMouseYChanged: {
            if(draging){
                var tempY=lastYPosition+(mouseY-pressY)
                if(tempY>0){
                    lastYPosition=lastYPosition-(column_airlist.height-buttonItemHeight*itemCount*2-columnSpacing*itemCount*2-1)
                }else if(tempY<-(column_airlist.height-root.height)){
                    lastYPosition=lastYPosition+buttonItemHeight*modelList+columnSpacing*modelList
                }
                column_airlist.tempY=tempY
                if(Math.abs(mouseY-pressY)>1){
                    moved=true
                }

            }
        }
        onPressed: {
            if(flickavailable){
                flickAnimation.stop()
                pressX=mouseX
                pressY=mouseY
                lastYPosition=column_airlist.y
                draging=true
                startFlicking()
                moved=false
            }
            press_()
        }
        onReleased: {
            if(flickavailable){
                draging=false
                flickSpeedTimer.stop()
                if(Math.abs(flickSpeedTimer.speed)>15){
                    flickingDelay(column_airlist.y+flickSpeedTimer.speed*6)
                }
            }
            if(!moved){
                release_()
            }
        }
    }
}
*/
Rectangle{
    id:contain_rectangle
    width: parent.width
    height: parent.height
    color: "black"
    clip:true
    property var maxValue:-10000//最大值
    property var minValue:10000//最小值
    property var middleValue:0//中位值
    property var percent: 0.1//最小刻度
    property int fixNum: 1
    Rectangle{
        width: parent.width
        height: 2
        anchors.centerIn: parent
        color: "white"
        opacity: 0.5
    }
    Rectangle{
        id:ruler
        width: 2
        height: parent.height
        color: "white"
        opacity: 0.5
        //计算出因该使用的刻度
        function findPercent(){
        }
        Column{
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.right
            Repeater{
                id:ruler_repater
                model: 21
                Item {
                    width: 4
                    height: ruler.height/ruler_repater.model
                    Rectangle{
                        height: 2
                        width: 4
                        anchors.centerIn: parent
                        color: "white"
                        Text {
                            anchors.left: parent.right
                            color: "white"
                            text:(index>=10?(middleValue-percent*(index-10)):(middleValue+percent*(10-index))).toFixed(fixNum)
                            font.pointSize: 10
                        }
                    }
                }
            }
        }
    }
    Rectangle{
        id:value_select
        visible: false
        width: parent.width*0.9
        height: parent.height*0.95
        color: "gray"
        anchors.centerIn: parent
        Grid{
            anchors.fill: parent
            id:value_select_grid
            columns: 6
            Repeater{
                model:20
                Rectangle{
                    width: value_select.width/6
                    height: width*0.55
                    color: "white"
                    border.color: "black"
                    border.width: 1
                    property var waveform
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            if(!parent.waveform){
                                parent.color=Qt.rgba((Math.random()*0.5+0.5), (Math.random()*0.5+0.5), (Math.random()*0.5+0.5), 1)
                                parent.waveform=painter_component.createObject(contain_rectangle,{"penColor":parent.color,"index":index})
                                text_timer.triggered.connect(parent.waveform.flash)
                                text_timer.start()
                            }else{
                                parent.color="white"
                                text_timer.triggered.disconnect(parent.waveform.flash)
                                parent.waveform.destroy()
                                parent.waveform=undefined
                            }
                        }
                    }
                    Text {
                        anchors.centerIn: parent
                        //text: flightInfoLoad?flight.analyzeValuelist[index]:0
                        color: "black"
                    }
                }
            }
        }
    }
    MouseArea{
        anchors.fill: parent
        onClicked: {
            maxValue+=1
        }

    }
}


