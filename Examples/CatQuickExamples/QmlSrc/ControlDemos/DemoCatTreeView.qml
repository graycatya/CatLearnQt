import QtQuick 2.12
import CatTreeModel 1.0
import ModelTool 1.0
import "../Common"

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
            height: 40
        }

        CatTreeView {
            id: cattreeview
            //width: cattreeheader.width
            sourceModel: cattreemodel
            clip: true

            anchors {
                right: parent.right
                top: cattreeheader.top
                left: parent.left
                bottom: parent.bottom
            }

            onExpand: {
                cattreemodel.expand(index)
            }

            onCollapse: {
                cattreemodel.collapse(index)
            }
        }

    }

    Item {
        id: rightRectangle
        anchors.top: parent.top
        anchors.left: leftRectangle.right
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.leftMargin: 10
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
