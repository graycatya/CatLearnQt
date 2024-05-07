import QtQuick 2.12
import CatTreeModel 1.0
import ModelTool 1.0
import QtQuick.Layouts 1.12
import QCatGrayQuick 1.0
import "../Common"
import "../"

Item {
    id: democattreeview

    Item {

        id: leftRectangle
        width: 320
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        anchors.leftMargin: 10

        CatTreeModel {
            id: cattreemodel
            onShowMessage: {

            }
        }

        CatTreeHeader {
            id: cattreeheader
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 36
            treeModel: cattreemodel
            treeView: cattreeview
        }

        CatTreeView {
            id: cattreeview
            //width: cattreeheader.width
            sourceModel: cattreemodel
            clip: true

            anchors {
                right: parent.right
                top: cattreeheader.bottom
                left: parent.left
                bottom: parent.bottom
                topMargin: 10
            }

            onExpand: {
                cattreemodel.expand(index)
            }

            onCollapse: {
                cattreemodel.collapse(index)
            }
        }

    }
    ColumnLayout {
        anchors.top: parent.top
        anchors.left: leftRectangle.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        spacing: 5
        Item {
            id: rightRectangle
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        RowLayout {
            Layout.preferredHeight: 30
            Layout.maximumHeight: 30
            Layout.fillWidth: true

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: "transparent"
            }

            CatButtonImage {
                id: addbutton
                Layout.preferredWidth: 30
                Layout.preferredHeight: 30

                backImage.width: addbutton.width
                backImage.height: addbutton.height
                btnImgNormal: ProjectObject.getCurrentResourcePath() + "AddImage.png"
                btnImgHovered: ProjectObject.getCurrentResourcePath() + "AddImage.png"
                btnImgPressed: ProjectObject.getCurrentResourcePath() + "AddImage.png"
                btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "AddImage.png"
                backgroundColor: ProjectObject.defaultButton_DefaultColor
                backgroundColor_hovered: ProjectObject.defaultButton_HoverColor
                backgroundColor_pressed: ProjectObject.defaultButton_PressColor
                imagebackground.border.width: addbutton.pressed ? 3 : (addbutton.hovered ? 1 : 0)
                imagebackground.border.color: ProjectObject.defaultButtonBorder_DefaultColor
                imagebackground.radius: 5
                onClicked: {
                    cattreeview.currentIndex = cattreemodel.addNode(cattreeview.currentIndex, {"name": "新建项"})
                    cattreeview.positionTo(cattreeview.currentIndex)
                }
            }

            CatButtonImage {
                id: clearbutton
                Layout.preferredWidth: 30
                Layout.preferredHeight: 30

                backImage.width: clearbutton.width
                backImage.height: clearbutton.height
                btnImgNormal: ProjectObject.getCurrentResourcePath() + "ClearImage.png"
                btnImgHovered: ProjectObject.getCurrentResourcePath() + "ClearImage.png"
                btnImgPressed: ProjectObject.getCurrentResourcePath() + "ClearImage.png"
                btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "ClearImage.png"
                backgroundColor: ProjectObject.defaultButton_DefaultColor
                backgroundColor_hovered: ProjectObject.defaultButton_HoverColor
                backgroundColor_pressed: ProjectObject.defaultButton_PressColor
                imagebackground.border.width: clearbutton.pressed ? 3 : (clearbutton.hovered ? 1 : 0)
                imagebackground.border.color: ProjectObject.defaultButtonBorder_DefaultColor
                imagebackground.radius: 5
                onClicked: {
                    //chartObject.clearData();
                    cattreemodel.remove(cattreeview.currentIndex)
                    cattreeview.currentIndex = -1
                }
            }

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: "transparent"
            }
        }
    }

    Component.onCompleted: {
        cattreeview.currentIndex = cattreemodel.addNode(cattreeview.currentIndex, {"name": "新建项"})
        cattreeview.positionTo(cattreeview.currentIndex)
        cattreeview.currentIndex = cattreemodel.addNode(cattreeview.currentIndex, {"name": "新建项"})
        cattreeview.positionTo(cattreeview.currentIndex)
        cattreeview.currentIndex = cattreemodel.addNode(cattreeview.currentIndex, {"name": "新建项"})
        cattreeview.positionTo(cattreeview.currentIndex)
    }

}
