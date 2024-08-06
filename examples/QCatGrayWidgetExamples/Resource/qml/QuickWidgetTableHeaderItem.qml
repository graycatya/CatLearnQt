import QtQuick 2.12

Rectangle {
    id: root
    readonly property var model: parent.model
    readonly property int columnIndex: parent.columnIndex
    readonly property int rowIndex: parent.rowIndex
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
           text: root.parent.headerData[rowIndex]
           color: StyleConfig.textColor

           font.pixelSize: 16
        }
    }
}
