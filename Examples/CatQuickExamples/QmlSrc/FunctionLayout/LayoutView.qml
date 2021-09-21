import QtQuick 2.12
import QtQml 2.12
import QtQuick.Controls 2.12
import "DefaultLayout"
import "GridLayout"
import "TreeLayout"
import "../"



Rectangle {
    id: layoutview
    color: "transparent"
    /*
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


        Component.onCompleted:{
            contentItem.highlightMoveDuration = 0       //将移动时间设为0
        }
    }
    */

    Loader {
        id: layoutloader
        anchors.fill: layoutview
        asynchronous: true
        visible: status == Loader.Ready
        source: ProjectObject.getProjectQmlLayoutPath() + "DefaultLayout/DefaultLayout.qml"

        onProgressChanged: {
            console.log("Progress: " + progress)
        }

    }

    Component.onCompleted: {
        ProjectObject.updateLayoutState.connect(function(layoutstate){
            if(ProjectObject.layoutState === ProjectObject.ListLayout)
            {
                layoutloader.source = ProjectObject.getProjectQmlLayoutPath() + "DefaultLayout/DefaultLayout.qml"
            } else if(ProjectObject.layoutState === ProjectObject.GridLayout) {
                layoutloader.source = ProjectObject.getProjectQmlLayoutPath() + "TreeLayout/CatTreeLayout.qml"
            } else if(ProjectObject.layoutState === ProjectObject.TreeLayout) {
                layoutloader.source = ProjectObject.getProjectQmlLayoutPath() + "GridLayout/CatGridLayout.qml"
            }
        });
    }

}
