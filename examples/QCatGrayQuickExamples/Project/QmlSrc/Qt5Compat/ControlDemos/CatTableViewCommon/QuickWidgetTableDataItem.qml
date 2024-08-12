import QtQuick 2.12
import QCatGrayQuick 1.0

CatTableViewItemBase {
    id: root
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
           text: datamodel ? datamodel.getStruct(columnIndex).data[headerData[rowIndex]] : ""
           color: "#C1C1C1"
           font.pixelSize: 16

        }
    }

}
