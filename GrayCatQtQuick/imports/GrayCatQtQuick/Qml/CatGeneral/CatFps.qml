//pragma Singleton
import QtQuick 2.12
import QtGraphicalEffects 1.12
Rectangle {
    id: root
    property int fps: 60 
    property int fpsCount: 0
    visible: true
    property color textColor: "white"
    property int textSize: 32
    implicitHeight: 32
    implicitWidth: 32

/*
    Image {
        id: fpsimage 
        source: "qrc:/svgfps.svg"
        width: source.width  
        height: source.height  
        //anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left 
        RotationAnimation on rotation {
            from: 0 
            to: 360 
            running: true 
            loops: Animation.Infinite
            duration: 1000
        }
        //旋转信号接收刷新fps实时值
        onRotationChanged: fpsCount++
    }*/

    Rectangle
    { 
        id: rect
        width: parent.width
        height: parent.height
        color: Qt.rgba(0, 0, 0, 0)
        radius: width / 2
        border.width: width / 6
        visible: false
    }
    ConicalGradient {
        width: rect.width 
        height: rect.height 
        gradient: Gradient 
        {
            GradientStop { position: 0.0; color: "#87CEFF" }
            GradientStop { position: 1.0; color: "blue" }
        }
        source: rect 
        RotationAnimation on rotation {
            from: 0 
            to: 360 
            duration: 1000 
            loops: Animation.Infinite
        }
        onRotationChanged: fpsCount++
    }
    

    Text {
        id: fpstext
        anchors.left: rect.right 
        anchors.verticalCenter: rect.verticalCenter
        text: "FPS" + fps 
        font.pixelSize: textSize
        style: Text.Outline 
        styleColor: "#606060"
        color: textColor
    }
    Timer {
        interval: 1000
        repeat: true 
        running: true 
        onTriggered: {
            fps = fpsCount 
            fpsCount = 0
        }
    }
}
