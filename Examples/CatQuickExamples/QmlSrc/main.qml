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

        TitleItem {

        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 2
            color: ProjectObject.titleBottomWidthColor
        }

        UiFlowView {
        }
    }

    //color: ""
    /*Image {
        id: img
        anchors.fill: parent
        source: "qrc:/Images/portrait.png"
        width: sourceSize.width
        height: sourceSize.height
    }*/

}
