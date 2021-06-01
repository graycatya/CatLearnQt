import QtQuick 2.12
//import QtQuick.Shapes 1.12
import QtQuick.Controls 2.12


Rectangle {
    id: root
    property var control: parent
    //property int linewidth: 2
    readonly property int recSize: 12
    width: recSize
    height: recSize 
    color: "#00FFFF"
    radius: width / 2
    anchors {
        top: parent.top
        horizontalCenter: parent.horizontalCenter
        topMargin: -20
    }

    Rectangle {
        id: rotateline
        color: root.color
        width: 2
        height: 10
        anchors {
            top: parent.bottom
            //水平中心
            horizontalCenter: parent.horizontalCenter
            topMargin: -2
        }
    }

    Image {
        id:rotateCursor
        source: "qrc:/svgrotate.svg"
        width: sourceSize.width * 0.6
        height: sourceSize.height * 0.6
        visible: rotateArea.containsMouse | rotateArea.pressed
        x: rotateArea.mouseX - width  / 2
        y: rotateArea.mouseY - height / 2
    }

    MouseArea {
        id: rotateArea
        anchors.centerIn: parent 
        width: parent.width * 2
        height: parent.height * 2
        hoverEnabled: true 
        property int lastX: 0
        onContainsMouseChanged: {
            if(containsMouse) {
                cursorShape = Qt.BlankCursor;
            } else {
                cursorShape = Qt.ArrowCursor;
            }
        }

        onPressedChanged: {
            if(containsPress) {
                lastX = mouseX;
            }
        }

        onPositionChanged: {
            if(pressed) {
                let t = control.rotation + (mouseX - lastX) / 5
                t = t % 360
                control.rotation = t
            }
        }

    }

    ToolTip {
        id: toolTop
        x: rotateArea.mouseX + 20
        y: rotateArea.mouseY 
        visible: rotateArea.pressed 
        contentItem: Text {
            text: parseInt(control.rotation) + "°"
        }
    }

}


