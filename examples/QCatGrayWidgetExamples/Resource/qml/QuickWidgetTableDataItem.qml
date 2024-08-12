import QtQuick 2.12
import QCatGrayQuick 1.0

CatTableViewDelegateBase {
    id: root
    delegate: Rectangle {
        clip: true
        width: datamodel.getHeaderStruct(index).preferredWidth
        height: datamodel.getStruct(columnindex).preferredHeight
        border.color: "#FFFFFF"
        border.width: 1
        color: "#000000"
        Text {
           anchors.fill: parent
           verticalAlignment: Text.AlignVCenter
           horizontalAlignment: Text.AlignHCenter
           text: datamodel.getStruct(columnindex).data[datamodel.headerTableData[index]]
           color: "#FFFFFF"
           font.pixelSize: 16

        }
    }

}
