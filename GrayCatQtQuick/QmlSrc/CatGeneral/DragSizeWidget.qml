import QtQuick 2.12

Rectangle {
    id: root 
    color: "transparent"
    border.width: 4
    border.color: "transparent"
    width: parent.width  
    height: parent.height  

     
    property color posborderColor: "#08a1ef"
    property color posColor: "white"

    property var control: parent
    readonly property int posRadius: 6

    Rectangle {
        border.color: posborderColor
        border.width: 2
        color: "transparent"
        radius: posRadius
        anchors.fill: parent 
        anchors.margins: -2
    }

    //top
    Rectangle {
        border.color: posborderColor
        border.width:  1
        color: posColor
        width: posRadius * 2
        height: width
        radius: width / 2
        anchors {
            top: parent.top
            horizontalCenter: parent.horizontalCenter
            topMargin: - width / 2
        }
    }

    //bottom 
    Rectangle {
        border.color: posborderColor 
        border.width: 1 
        color: posColor 
        width: posRadius * 2 
        height: width 
        radius: width / 2
        anchors {
            bottom: parent.bottom 
            horizontalCenter: parent.horizontalCenter
            bottomMargin: - width / 2
        }
    }

    //left
    Rectangle {
        border.color: posborderColor
        border.width:  1
        color: posColor
        width: posRadius * 2
        height: width
        radius: width / 2
        anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
            leftMargin: - width / 2
        }
    }

    //right 
    Rectangle {
        border.color: posborderColor 
        border.width: 1 
        color: posColor 
        width: posRadius * 2 
        height: width  
        radius: width / 2
        anchors {
            right: parent.right 
            verticalCenter: parent.verticalCenter
            rightMargin: - width / 2
        }
    }

    //topleft 
    Rectangle {
        border.color: posborderColor 
        border.width: 1 
        color: posColor 
        width: posRadius * 2 
        height: width  
        radius: width / 2
        anchors {
            left: parent.left
            verticalCenter: parent.top
            leftMargin: - width / 2
        }
    }

    //bottomleft 
    Rectangle {
        border.color: posborderColor 
        border.width: 1 
        color: posColor 
        width: posRadius * 2 
        height: width  
        radius: width / 2
        anchors {
            left: parent.left
            verticalCenter: parent.bottom
            leftMargin: - width / 2
        }
    }

    //topright 
    Rectangle {
        border.color: posborderColor 
        border.width: 1 
        color: posColor 
        width: posRadius * 2 
        height: width  
        radius: width / 2
        anchors {
            right: parent.right
            verticalCenter: parent.top
            rightMargin: - width / 2
        }
    }

    //bottomright 
    Rectangle {
        border.color: posborderColor 
        border.width: 1 
        color: posColor 
        width: posRadius * 2 
        height: width  
        radius: width / 2
        anchors {
            right: parent.right
            verticalCenter: parent.bottom
            rightMargin: - width / 2
        }
    }

    //左边拖动大小
    DragWidget {
        id: leftdragsize
        y: root.border.width  
        height: root.height - border.width * 2
        mouseStyle: Qt.SizeHorCursor
        onPosDragWidget: {
            if(root.control.x + pos.x < root.control.x + root.control.width)
            {
                root.control.x += pos.x
            }
            if(root.control.width - pos.x > 0)
            {
                root.control.width -= pos.x
            }
        }
    }

    //右边拖动大小
    DragWidget {
        id: rightdragsize
        x: parent.width - width
        y: root.border.width
        height: root.height - border.width * 2
        mouseStyle: Qt.SizeHorCursor
        onPosDragWidget: {
            if(root.control.width + pos.x > 0)
            {
                root.control.width += pos.x
            }
        }
    }

    //顶边拖动大小
    DragWidget {
        id: topdragsize
        x: root.border.width  
        width: root.width - border.width * 2
        mouseStyle: Qt.SizeVerCursor
        onPosDragWidget: {
            if(root.control.y + pos.y < root.control.height + root.control.y)
            {
                root.control.y += pos.y
            }
            if(root.control.height - pos.y > 0)
            {
                root.control.height -= pos.y
            }
        }
    }

    //底边拖动大小
    DragWidget {
        id: bottomdragsize
        x: root.border.width 
        y: parent.height - height
        width: root.width - border.width * 2
        mouseStyle: Qt.SizeVerCursor
        onPosDragWidget: {
            console.log("root.x", root.x);
            console.log("root.y", root.y);
            console.log("bottomdragsize.x ", bottomdragsize.x);
            console.log("bottomdragsize.y ", bottomdragsize.y);
            if(root.control.height + pos.y > 0)
            {
                root.control.height += pos.y
            }
        }
    }

    //左上角拖动大小 - 左上角坐标为 0,0
    DragWidget {
        id: lefttopdragsize
        mouseStyle: Qt.SizeFDiagCursor
        onPosDragWidget: {
            
            if(root.control.x + pos.x < root.control.x + root.control.width)
            {
                root.control.x += pos.x;
            }
            if(root.control.y + pos.y < root.control.y + root.control.height)
            {
                root.control.y += pos.y;
            }
            if(root.control.width - pos.x > 0)
            {
                root.control.width -= pos.x;
            }
            if(root.control.height - pos.y > 0)
            {
                root.control.height -= pos.y;
            }
        }
    }

    //左下角拖动大小
    DragWidget {
        id: leftbottomdragsize
        y: parent.height - height 
        mouseStyle: Qt.SizeBDiagCursor
        //control: parent
        onPosDragWidget: {
            if(root.control.x + pos.x < root.control.x + root.control.width)
            {
                root.control.x += pos.x
            }
            if(root.control.width - pos.x > 0)
            {
                root.control.width -= pos.x
            }
            if(root.control.height + pos.y > 0)
            {
                root.control.height += pos.y
            }
        }
    }

    //右上角拖动大小
    DragWidget {
        id: righttopdragsize
        x: parent.width - width  

        mouseStyle: Qt.SizeBDiagCursor
        onPosDragWidget: {
            if(root.control.y + pos.y < root.control.height + root.control.y)
            {
                root.control.y += pos.y
            }
            if(root.control.height - pos.y > 0)
            {
                root.control.height -= pos.y
            }
            if(root.control.width + pos.x > 0)
            {
                root.control.width += pos.x
            }
        }
    }

    //右下角拖动大小
    DragWidget {
        id: rightbottomdragsize
        x: parent.width - width  
        y: parent.height - height 

        mouseStyle: Qt.SizeFDiagCursor
        onPosDragWidget: {
            console.log("pos.x " + pos.x);
            console.log("pos.y " + pos.y);
            if(root.control.width + pos.x > 0)
            {
                root.control.width += pos.x
            }
            if(root.control.height + pos.y > 0)
            {
                root.control.height += pos.y
            }
        }
    }

}
