import QtQuick 2.12
import QtQuick.Controls 2.12
import "DefaultLayout"



Rectangle {
    id: layoutview
    color: "transparent"
    SwipeView {
        id: functionswipeview
        anchors.centerIn: layoutview
        anchors.fill: layoutview
        currentIndex: 0
        interactive: false
        spacing: 5

        DefaultLayout {
            id: defaultlayout
        }

        clip: true

        onCurrentIndexChanged: {
            ThickCloudConfigObject.mainViewFunc = functionswipeview.currentIndex
        }


        Component.onCompleted:{
            contentItem.highlightMoveDuration = 0       //将移动时间设为0
        }
    }

}
