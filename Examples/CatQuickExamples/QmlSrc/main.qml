import QtQuick 2.12
import QtQuick.Layouts 1.12
import GrayCatQtQuick 1.0


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
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: ProjectObject.appBackgroundColor
        }


    }

    CatFps {
        anchors.right: parent.right
        y: win10titleitem.height
    }

    Component.onCompleted: {
        catLog.debug_print("run ui");
    }


}
