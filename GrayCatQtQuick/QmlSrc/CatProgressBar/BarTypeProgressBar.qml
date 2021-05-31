import QtQuick 2.12 

Rectangle {
    id: root 
    //进度条颜色
    property alias progressbarColor: progressbar.color
    //进度条值
    property int value: 0
    property string backgroundColor: "transparent" 
    property string backgroundBorderColor: "green"
    property int backgroundBorderWidth: 0
    property alias running: animation.running
    property alias duration: numberanimation.duration

    color: backgroundColor
    antialiasing: true
    width: 200; height: 15

    radius: 0  //设置矩形圆角弧度
    border.color: backgroundBorderColor //设置边框的颜色
    border.width: backgroundBorderWidth   //设置边框的大小

    Rectangle {
        id: progressbar 
        //anchors.centerIn: parent
        border.color: "transparent" //设置边框的颜色
        //radius: root.radius  //设置矩形圆角弧度
        border.width: root.border.width  //设置边框的大小

        color: "gray"
        x: root.border.width; y: root.border.width;
        height: root.height - border.width*2
        width:value - border.width*2
    }
    SequentialAnimation {
        id: animation 
        loops: Animation.Infinite 
        running: false
        NumberAnimation {
            id: numberanimation
            target: progressbar 
            properties: "width"
            from: 0 
            to: root.width - root.border.width*2
            //duration: root.duration
        }
    }
}
