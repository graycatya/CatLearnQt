import QtQuick
import QtQuick.Layouts
import QCatGrayQuick

import QtQuick.Controls
import "../"

Item {


    ColumnLayout {
        id: columnlayout
        anchors.fill: parent
        anchors.topMargin: 0
        anchors.leftMargin: 50
        anchors.rightMargin: 50
        anchors.bottomMargin: 10
        spacing: 20

        Text {
            id: layouttext
            Layout.fillWidth: true
            Layout.preferredHeight: 21
            text: qsTr("Layout")
            font.pixelSize: 18
            font.family: ProjectObject.fontFamily
            font.bold: true
            color: ProjectObject.defaultTextColor
        }
        ButtonGroup {
            buttons: layoutbuttons.children
        }
        RowLayout {
            id: layoutbuttons
            Layout.fillWidth: true
            Layout.preferredHeight: 80
            Layout.maximumHeight: 80
            spacing: 20

            CatButton {
                id: listbutton
                checkable: true;
                checked: true
                Layout.preferredWidth: 80
                Layout.preferredHeight: 80
                background: Rectangle {
                    color: "transparent"

                    radius: 5


                    Image {
                        id: listbuttonimg
                        source: ProjectObject.getCurrentResourcePath() + "ListLayout.png"
                        width: sourceSize.width
                        height: sourceSize.height
                    }

                    CatDropShadow {
                        anchors.fill: listbuttonimg
                        horizontalOffset: 0
                        verticalOffset: 0
                        radius: 5.0
                        samples: 10
                        color: ProjectObject.defaultShadowColor
                        source: listbuttonimg
                    }

                    Rectangle {

                        color: "transparent"
                        border.width: listbutton.checked ? 1 : 0
                        border.color: "#C9AE75"
                        anchors.fill: parent
                        radius: 5
                        clip: true
                    }
                }

                onClicked: {
                    ProjectObject.layoutState = ProjectObject.ListLayout
                }

            }

            CatButton {
                id: treebutton
                checkable: true;
                Layout.preferredWidth: 80
                Layout.preferredHeight: 80
                background: Rectangle {
                    color: "transparent"
                    radius: 5


                    Image {
                        id: treebuttonimg
                        source: ProjectObject.getCurrentResourcePath() + "TreeLayout.png"
                        width: sourceSize.width
                        height: sourceSize.height
                    }

                    CatDropShadow {
                        anchors.fill: treebuttonimg
                        horizontalOffset: 0
                        verticalOffset: 0
                        radius: 5.0
                        samples: 10
                        color: ProjectObject.defaultShadowColor
                        source: treebuttonimg
                    }

                    Rectangle {

                        color: "transparent"
                        border.width: treebutton.checked ? 1 : 0
                        border.color: "#C9AE75"
                        anchors.fill: parent
                        radius: 5
                    }
                }

                onClicked: {
                    ProjectObject.layoutState = ProjectObject.GridLayout
                }

            }

            CatButton {
                id: gridbutton
                checkable: true;
                Layout.preferredWidth: 80
                Layout.preferredHeight: 80
                background: Rectangle {
                    color: "transparent"
                    radius: 5

                    Image {
                        id: gridbuttonimg
                        source: ProjectObject.getCurrentResourcePath() + "GridLayout.png"
                        width: sourceSize.width
                        height: sourceSize.height
                    }

                    CatDropShadow {
                        anchors.fill: gridbuttonimg
                        horizontalOffset: 0
                        verticalOffset: 0
                        radius: 5.0
                        samples: 10
                        color: ProjectObject.defaultShadowColor
                        source: gridbuttonimg
                    }

                    Rectangle {

                        color: "transparent"
                        border.width: gridbutton.checked ? 1 : 0
                        border.color: "#C9AE75"
                        anchors.fill: parent
                        radius: 5
                    }
                }

                onClicked: {
                    ProjectObject.layoutState = ProjectObject.TreeLayout
                }

            }

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }

        Rectangle {
            id: line_0
            Layout.fillWidth: true
            Layout.preferredHeight: 1
            Layout.topMargin: 10
            color: ProjectObject.lineColor
        }

        Item {
            id: transitionItem
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            Layout.topMargin: 10
            CatBasicsText {
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                color: ProjectObject.defaultTextColor
                text: qsTr("Transition")
                font.family: ProjectObject.fontFamily
                font.pixelSize: 18
                font.bold: true
                horizontalAlignment: Text.AlignLeft
            }

            Switch {
                id: switchtransition
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: 9
                width: 60
                height: 32
                checked: ProjectObject.settingtransition
                //checked: model.value["Value"]
                indicator: Rectangle {
                    width: 60
                    height: 32
                    radius: height / 2
                    color: switchtransition.checked ? ProjectObject.switchbuttonback_CheckColor : ProjectObject.switchbuttonback_DefaultColor
                    border.width: 2
                    border.color: ProjectObject.switchbuttonback_CheckColor

                    Rectangle {
                        id: switchtransitioncircle
                        x: 1
                        width: switchtransition.checked ? parent.height - 4 : parent.height - 2
                        height: width
                        radius: width / 2
                        anchors.verticalCenter: parent.verticalCenter
                        color: ProjectObject.switchbuttonCircle_Color
                        //border.color: "#C4C4C4"

                        NumberAnimation on x {
                            id: switchtransitioncircleAnimation
                            duration: 200
                        }

                        function animationTo()
                        {
                            switchtransitioncircleAnimation.from = x
                            switchtransitioncircleAnimation.to = switchtransition.checked ? parent.width - width - 1 : 1
                            switchtransitioncircleAnimation.restart();
                        }
                    }
                }

                onVisualPositionChanged: {
                    ProjectObject.settingtransition = checked
                    switchtransitioncircle.animationTo()
                    //console.log("fsdafa; " + checked)
                }
            }
        }

        Item {
            //color: "#000000"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

    }

}
