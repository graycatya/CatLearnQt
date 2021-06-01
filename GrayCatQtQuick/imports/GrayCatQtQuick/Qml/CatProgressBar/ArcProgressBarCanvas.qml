import QtQuick 2.12

Rectangle {
    id: root 
    color: "transparent"
    border.color: "transparent"
    antialiasing: true
    //半径 背景和进度条共用
    property int radiusCanvas: 50
    //背景起始与结束角度 已转换为百分比 
    property double backgroundStartValue: -25
    property double backgroundEndValue: 100
    //进度条背景颜色，宽度
    property color backgroundColor: "gray"
    property int backgroundLineWidth: 5

    //进度条进度与结束角度 已转换为百分比 
    property double value: 50
    property double progressBarStartValue: -25
    //进度条颜色，宽度
    property color progressBarColor: "blue"
    property int progressbarLineWidth: 5
    //顺时针 加载
    property bool clockwise: true


    Canvas {
        id: background
        anchors.fill: parent
        antialiasing: true
        property var ctx;
        onPaint: {
            ctx = getContext("2d");
            ctx.clearRect(0, 0, background.width, background.height);
            ctx.strokeStyle = root.backgroundColor;
            ctx.lineWidth = root.backgroundLineWidth;
            ctx.beginPath();
            ctx.arc(root.width/2, 
                            root.height/2, 
                            root.radiusCanvas, 
                            (Math.PI*2)*(root.backgroundStartValue/100), 
                            (Math.PI*2)*((root.backgroundEndValue + root.backgroundStartValue)/100), false);
            ctx.stroke();
        }
    }

    Canvas {
        id: progressbar
        anchors.fill: parent
        antialiasing: true
        property var ctx;
        onPaint: {
            ctx = getContext("2d");
            ctx.clearRect(0, 0, progressbar.width, progressbar.height);
            ctx.strokeStyle = root.progressBarColor;
            ctx.lineWidth = root.progressbarLineWidth;
            ctx.beginPath();
            ctx.arc(root.width/2, 
                            root.height/2, 
                            root.radiusCanvas, 
                            (Math.PI*2)*(root.progressBarStartValue/100), 
                            (Math.PI*2)*((root.value + progressBarStartValue)/100), !clockwise);
            ctx.stroke();
        }

    }

    onValueChanged: {
        progressbar.requestPaint();
    }

}
