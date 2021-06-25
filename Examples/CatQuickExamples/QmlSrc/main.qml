import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import GrayCatQtQuick 1.0
import "FunctionLayout"


Rectangle {
    id: root
    width: 800
    height: 600

    property bool isMaxed: view.isMax

    color: ProjectObject.appBackgroundColor

    ColumnLayout {
        id: rootLayout
        spacing: 0
        anchors.fill: parent
        anchors.topMargin: isMaxed ? 8 : 0
        anchors.leftMargin: isMaxed ? 8 : 0
        anchors.rightMargin: isMaxed ? 8 : 0
        anchors.bottomMargin: isMaxed ? 8 : 0


        Win10TitleItem {
            id: win10titleitem
            Layout.fillWidth: true
            Layout.preferredHeight: 40
            Layout.maximumHeight: 40
            Layout.minimumHeight: 40
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 2
            color: ProjectObject.titleBottomWidthColor
        }

        Rectangle {
            id: functionRect
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.topMargin: 20
            Layout.leftMargin: 20
            Layout.rightMargin: 20
            Layout.bottomMargin: 20
            color: ProjectObject.appBackgroundColor

            LayoutView {
                anchors.fill: functionRect
            }

            CatFps {
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


    Component.onCompleted: {
        catLog.debug_print("run ui");
    }


}
