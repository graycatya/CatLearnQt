//pragma Singleton
import QtQuick
import "../CatGraphicalEffects"
Item {
    id: root
    readonly property string version: "1.0"
    property int fps: 60 
    property int fpsCount: 0
    visible: true
    property color textColor: "white"
    property int textSize: 32
    property int fpsWidth: 32
    property int fpsHeight: 32
    property color gradient0Color: "#87CEFF"
    property color gradient1Color: "blue"

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
        width: parent.fpsWidth
        height: parent.fpsHeight
        color: Qt.rgba(0, 0, 0, 0)
        radius: width / 2
        border.width: width / 6
        visible: false
    }
    CatConicalGradient {
        width: rect.width 
        height: rect.height 
        gradient: Gradient 
        {
            GradientStop { position: 0.0; color: root.gradient0Color }
            GradientStop { position: 1.0; color: root.gradient1Color }
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
