import QtQuick 2.12
import QtQuick.Layouts 1.12
import GrayCatQtQuick 1.0
import QtGraphicalEffects 1.12
import QtQuick.Controls 2.12
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

                    DropShadow {
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

                    DropShadow {
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

                    DropShadow {
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

        Item {
            //color: "#000000"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

    }

}
