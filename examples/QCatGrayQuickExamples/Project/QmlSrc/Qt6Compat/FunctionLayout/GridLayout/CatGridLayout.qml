import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QCatGrayQuick
import "../../"

Rectangle {
    id: catgridlayout
    color: "transparent"

    SwipeView {
        id: gridlayoutSwipeView

        anchors.fill: parent
        anchors.margins: 30

        currentIndex: 0
        interactive: false
        spacing: 5
        clip: true

        CatGridListView {
            id: catgridlistview
        }

        Rectangle {
            //anchors.fill: parent
            color: "transparent"

            Rectangle {
                id: demonstrationview
                anchors.fill: parent
                anchors.margins: 5
                color: ProjectObject.defaultRectangleColor
                radius: 5
                property string controlname: "--------"

                Text {
                    id: controlnametext
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.topMargin: 20
                    anchors.leftMargin: 40
                    text: demonstrationview.controlname
                    font.pixelSize: 26
                    font.family: ProjectObject.fontFamily
                    font.bold: true
                    color: ProjectObject.controlNameColor
                }

                CatButtonImage {
                    id: returnButton
                    anchors.top: parent.top
                    anchors.right: parent.right
                    anchors.topMargin: 20
                    anchors.rightMargin: 30
                    btnImgUrl:  ProjectObject.getCurrentResourcePath() + "Return.png"
                    width: 40
                    height: 40

                    onClicked: {
                        gridlayoutSwipeView.currentIndex = 0
                    }
                }

                Loader {
                    id: pageloader
                    anchors.top: controlnametext.bottom
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.topMargin: 10
                    anchors.leftMargin: 0
                    anchors.rightMargin: 0
                    anchors.bottomMargin: 0
                    asynchronous: true
                    visible: status == Loader.Ready
                    source: ProjectObject.defaultControl.control[0].qmlSource

                    onProgressChanged: {
                        console.log("Progress: " + progress)
                    }
                }

                function updatedemo(demoname, qmlsource)
                {
                    controlname = demoname
                    pageloader.source = qmlsource
                    gridlayoutSwipeView.currentIndex = 1
                }

                Component.onCompleted: {
                    controlname = ProjectObject.defaultControl.control[0].name
                }
            }

            CatDropShadow {
                anchors.fill: demonstrationview
                horizontalOffset: 0
                verticalOffset: 0
                radius: 5.0
                samples: 10
                color: ProjectObject.defaultShadowColor
                source: demonstrationview
            }

        }

        /*Loader {
            id: pageloader
            asynchronous: true
            visible: status == Loader.Ready
            source: ProjectObject.defaultControl.control[0].qmlSource

            onProgressChanged: {

            }
        }*/

        Component.onCompleted: {
            contentItem.highlightMoveDuration = 0       //将移动时间设为0
        }
    }

}
