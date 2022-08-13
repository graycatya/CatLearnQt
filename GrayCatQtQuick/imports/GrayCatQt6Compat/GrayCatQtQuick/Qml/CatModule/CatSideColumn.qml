import QtQuick 2.12
import QtQuick.Layouts 1.12

Rectangle {
    id: catsidecolumn
    property int minWidth: 60
    property int maxWidth: 200
    property string fontfamily: "Ubuntu"
    property int fontpixsize: 14
    property color fontcolor: "#FFFFFF"
    property alias listviewitem: listview
    property bool showhighlight: false
    property bool sideslip: true

    state: "hideText"

    signal currentindex(int index);

    MouseArea {
        id: transarea

        anchors.fill: parent
        // 悬停事件是否被处理
        hoverEnabled: true
        /* 此属性保存组合的鼠标事件
         * 是否会自动传播到与此鼠标区域重叠但视觉堆叠顺序较低的其他鼠标区域
        */
        //propagateComposedEvents: true
        // 此属性保存此鼠标区域的光标形状
        cursorShape: enabled ? Qt.PointingHandCursor : Qt.ForbiddenCursor

        //将accept设置为true将防止鼠标事件传播到此项下面的项。
        onDoubleClicked: { mouse.accepted = false; }
        onPositionChanged: {
            mouse.accepted = false;
        }
        onPressed: {
            mouse.accepted = false;
        }
        onPressAndHold: {
            mouse.accepted = false;
        }
        onClicked: {
            mouse.accepted = false;
        }
        onReleased: {
            mouse.accepted = false;
        }

        onEntered: {
            if(sideslip)
            {
                catsidecolumn.state = "showText"
            }
        }

        onExited: {
            if(sideslip)
            {
                catsidecolumn.state = "hideText"
            }
        }

        ListView {
            id: listview
            anchors.fill: parent

            clip: true

            boundsBehavior: Flickable.StopAtBounds

            delegate: Rectangle {
                height: minWidth
                width: catsidecolumn.width
                RowLayout {
                    anchors.fill: parent
                    spacing: 10
                    Image {
                        source: itemimgsource
                        Layout.preferredWidth: catsidecolumn.minWidth
                        Layout.preferredHeight: catsidecolumn.maxWidth
                    }
                    Text {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        font.family: catsidecolumn.fontfamily
                        font.pixelSize: catsidecolumn.fontpixsize
                        color: catsidecolumn.fontcolor
                        verticalAlignment: Text.AlignVCenter

                        text: itemtext

                        visible: catsidecolumn.state === "hideText" ? false : true

                    }
                    Item {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                }
            }
        }
    }

    states: [
        State {
            name: "hideText"
            PropertyChanges {
                target: catsidecolumn
                width: minWidth
                Layout.preferredWidth: minWidth
            }
        },
        State {
            name: "showText"
            PropertyChanges {
                target: catsidecolumn
                width: maxWidth
                Layout.preferredWidth: maxWidth
            }
        }
    ]

    transitions: [
        Transition {
            from: "hideText"
            to: "showText"
            NumberAnimation {
                properties: "width"
                target: catsidecolumn
                from: width
                to: maxWidth
                duration: 500
            }
            NumberAnimation {
                properties: "Layout.preferredWidth"
                target: catsidecolumn
                from: Layout.preferredWidth
                to: maxWidth
                duration: 500
            }
        },
        Transition {
            from: "showText"
            to: "hideText"
            NumberAnimation {
                properties: "width"
                target: catsidecolumn
                from: width
                to: minWidth
                duration: 500
            }
            NumberAnimation {
                properties: "Layout.preferredWidth"
                target: catsidecolumn
                from: Layout.preferredWidth
                to: minWidth
                duration: 500
            }
        }
    ]

    onCurrentindex: {
        listview.currentIndex = index;
    }

}
