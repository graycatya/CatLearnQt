import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Rectangle {
    Layout.fillWidth: true
    Layout.fillHeight: true
    color: ProjectObject.appBackgroundColor
/*
anchors.topMargin: 50
anchors.leftMargin: 95
anchors.rightMargin: 95
anchors.bottomMargin: 50
*/
    SwipeView {
        id: functionswipeview
        //anchors.centerIn: parent
        anchors.fill: parent
        currentIndex: 0
        interactive: false
        spacing: 5

        clip: true

        SwipeView {
            id: functionlayoutview
            //anchors.centerIn: parent
            currentIndex: 0
            interactive: false
            spacing: 5

            GridLayoutView {
            }

            onCurrentIndexChanged: {
                //ThickCloudConfigObject.mainViewFunc = functionswipeview.currentIndex
            }


            Component.onCompleted:{
                contentItem.highlightMoveDuration = 0       //将移动时间设为0
            }
        }

        onCurrentIndexChanged: {
            //ThickCloudConfigObject.mainViewFunc = functionswipeview.currentIndex
        }


        Component.onCompleted:{
            contentItem.highlightMoveDuration = 0       //将移动时间设为0
        }
    }
}
