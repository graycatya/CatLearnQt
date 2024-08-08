import QtQuick 2.12

Rectangle {
    id: root
    readonly property var model: parent.parent.model
    readonly property int columnIndex: parent.parent.columnIndex
    readonly property int rowIndex: parent.parent.rowIndex
    readonly property var headerData: parent.parent.headerData
    Loader {
        id: itemLoader
        anchors.centerIn: parent
        sourceComponent: textstate
    }

    Component {
        id: textstate
        Text {
           id: tabletext
           anchors.fill: parent
           verticalAlignment: Text.AlignVCenter
           horizontalAlignment: Text.AlignHCenter
           text: headerData[rowIndex]
           color: StyleConfig.textColor

           font.pixelSize: 16
        }
    }
}
