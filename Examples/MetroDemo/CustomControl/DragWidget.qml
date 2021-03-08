import QtQuick 2.12

Item {
    id: root

    signal posDragWidget(point pos)

    property alias containsMouse: mouseArea.containsMouse
    property int mouseStyle: Qt.ArrowCursor
    //property bool drag: true
    property bool hoverenabled: true
    implicitWidth: 4   
    implicitHeight: 4
    
    property var control: parent

    signal clicked(real x, real y)
    signal doubleClicked(real x, real y)

    MouseArea {
        id: mouseArea
        anchors.fill: parent 
        //打开鼠标悬停事件
        hoverEnabled: hoverenabled

        property point lastPoint: Qt.point(0, 0)

        //鼠标按下事件
        onPressed: {
            lastPoint = Qt.point(mouseX, mouseY)
        }

        //鼠标在当前模块内事件
        onContainsMouseChanged: {
            if(containsMouse)
            {
                cursorShape = mouseStyle;
            } else {
                cursorShape = Qt.ArrowCursor;
            }
        }

        //鼠标位置发生改变时事件
        onPositionChanged: {
            if(drag && pressed && control)
            {
                posDragWidget(Qt.point(mouseX - lastPoint.x, mouseY - lastPoint.y));
            }
        }

        //鼠标点击
        onClicked: {
            root.clicked(mouseX, mouseY)
        }

        //鼠标双击
        onDoubleClicked: {
            root.doubleClicked(mouseX, mouseY)
        }

    }
}