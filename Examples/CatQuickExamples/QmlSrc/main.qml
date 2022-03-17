import QtQuick 2.12
import QtQuick.Window 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import GrayCatQtQuick 1.0
//import CatEncp 1.0
import "FunctionLayout"
import "./MoreFunctionViews"
import GrayFramelesshelper.Utils 1.0



Window {
    id: root
    visible: true
    width: 800
    height: 600

    minimumWidth: 800
    minimumHeight: 600

    //property bool isMaxed: view.isMax

    //property real _flh_margin: ((root.visibility === root.Maximized) || (root.visibility === root.FullScreen)) ? 0 : (Utils.frameBorderThickness / Screen.devicePixelRatio)
    property var _win_prev_state: null

    //color: ProjectObject.appBackgroundColor
    FramelessHelper {
        id: framelessHelper
    }

    ColumnLayout {
        id: rootLayout
        spacing: 0
        anchors.fill: parent
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            //Layout.topMargin: root._flh_margin
            //Layout.leftMargin: root._flh_margin
            //Layout.rightMargin: root._flh_margin
            Layout.preferredHeight: 40
            Layout.maximumHeight: 40
            Layout.minimumHeight: 40
            Win10TitleItem {
                id: win10titleitem
                anchors.fill: parent

            }

            DropShadow {
                anchors.fill: win10titleitem
                horizontalOffset: 0
                verticalOffset: 0
                radius: 8.0
                samples: 18
                color: ProjectObject.catPopupdropshadowColor
                source: win10titleitem
            }

        }



        Item {
            id: functionRect
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.topMargin: 20
            Layout.leftMargin: 20
            Layout.rightMargin: 20
            Layout.bottomMargin: 20
            //color: ProjectObject.appBackgroundColor

            LayoutView {
                anchors.fill: functionRect
            }

            CatFps {
                id: catfps
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.rightMargin: -15
                anchors.topMargin: -15
                gradient0Color: ProjectObject.fpsgradient0Color
                gradient1Color: ProjectObject.fpsgradient1Color
                width: 120
                height: 32
            }
        }
    }


    MoreView {
        id: moreview
        visible: false
    }




    Component.onCompleted: {
        framelessHelper.removeWindowFrame()
        console.log("run ui, system is: " + Qt.platform.os);
        console.log("webresourcepath " + catconfig.getWebResourcePath())
        ProjectObject.currentTheme = catconfig.getValue("Style");

        if(Qt.platform.os === "osx")
        {
            catfps.anchors.rightMargin = 0
        }

        color = ProjectObject.appBackgroundColor
        ProjectObject.updateCurrentThemeed.connect(function(){
            animation.start();
        });

        /*view.moveWindow.connect(function(){

            view.moveupdateUi();

        });*/

        //catLog.debug_print("system font familys: " + catconfig.systemFontFamily())

    }


    PropertyAnimation  {
        id: animation
        target: root;
        property: "color";
        from: color
        to: ProjectObject.appBackgroundColor
        duration: ProjectObject.settingtransition ? 400 : 0
    }


}
