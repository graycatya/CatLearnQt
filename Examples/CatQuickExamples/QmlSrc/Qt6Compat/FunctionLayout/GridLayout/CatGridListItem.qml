import QtQuick
import QtQuick.Controls

import GrayCatQtQuick
import "../../"

Item {
    id: catgridlistitem
    width: 320
    height: 440
    property string controlName: "------"
    property string author: "------"
    property string version: "------"
    property string logoSource: ""
    property string qmlSource: ""
    signal opencontrol(string controlname, string qmlsource)


        Rectangle {
            id: gridItemRect
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            anchors.topMargin: 20
            anchors.bottomMargin: 20
            radius: 6
            color: ProjectObject.controlRectangleColor

            MouseArea {
                id: transarea

                anchors.fill: parent
                hoverEnabled: true
                cursorShape: enabled ? Qt.PointingHandCursor : Qt.ForbiddenCursor
                onDoubleClicked: { mouse.accepted = false; }
                onPositionChanged: {

                }
                onPressed: {

                }
                onPressAndHold: {

                }
                onClicked: {
                    console.log("clicked: " + qmlSource);
                    demonstrationview.updatedemo(controlName, qmlSource)
                }
                onReleased: {
                    mouse.accepted = false;
                }

                onEntered: {
                    gridItemRect.state = "move"
                }

                onExited: {
                    gridItemRect.state = "default"
                }

                Rectangle {
                    id: imgRectItem
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: 250
                    color: ProjectObject.gridCardColor

                    Image {
                        id: logoimg
                        source: catgridlistitem.logoSource.length > 0 ? ProjectObject.getCurrentResourcePath() + catgridlistitem.logoSource : ""
                        width: 120
                        height: 120
                        anchors.centerIn: parent
                    }
                }

                CatBasicsText {
                    text: catgridlistitem.controlName
                    font.family: ProjectObject.fontFamily
                    font.pixelSize: 20
                    font.bold: true
                    color: ProjectObject.defaultTextColor
                    anchors.top: imgRectItem.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.topMargin: 20
                    height: 23
                }

                Text {
                    id: authortext
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.bottomMargin: 20
                    anchors.leftMargin: 25
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.bold: true
                    text: qsTr("Author: %1").arg(catgridlistitem.author)
                    font.pixelSize: 12
                    color: ProjectObject.controlAuthorColor
                }

                Text {
                    id: versiontext
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    anchors.bottomMargin: 20
                    anchors.rightMargin: 25
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.bold: true
                    text: qsTr("Version: %1").arg(catgridlistitem.version)
                    font.pixelSize: 12
                    color: ProjectObject.controlVersionColor
                }

                // 解决button侧栏圆角问题 buttonsRect
                layer.enabled: true
                layer.effect: CatOpacityMask{
                    maskSource: Rectangle{
                        width: gridItemRect.width
                        height: gridItemRect.height
                        radius: 6
                    }
                }
            }

            states: [
                State {
                    name: "default"
                    PropertyChanges {
                        target: gridItemRect
                        anchors.topMargin: 20
                        anchors.bottomMargin: 20
                    }
                },
                State {
                    name: "move"
                    PropertyChanges {
                        target: gridItemRect
                        anchors.topMargin: 15
                        anchors.bottomMargin: 25
                    }
                }

            ]

            transitions: [
                Transition {
                    from: "default"
                    to: "move"
                    NumberAnimation {
                        targets: [gridItemRect];
                        properties: "anchors.topMargin"
                        from: 20
                        to: 15
                        duration: 100
                    }
                    NumberAnimation {
                        targets: [gridItemRect];
                        properties: "anchors.bottomMargin"
                        from: 20
                        to: 25
                        duration: 100
                    }
                },
                Transition {
                    from: "move"
                    to: "default"
                    NumberAnimation {
                        targets: [gridItemRect];
                        properties: "anchors.topMargin"
                        from: 15
                        to: 20
                        duration: 100
                    }
                    NumberAnimation {
                        targets: [gridItemRect];
                        properties: "anchors.bottomMargin"
                        from: 25
                        to: 20
                        duration: 100
                    }
                }
            ]

        }

        CatDropShadow {
            anchors.fill: gridItemRect
            horizontalOffset: 0
            verticalOffset: 0
            radius: 8.0
            samples: 16
            color: ProjectObject.defaultShadowColor
            source: gridItemRect
        }

}
