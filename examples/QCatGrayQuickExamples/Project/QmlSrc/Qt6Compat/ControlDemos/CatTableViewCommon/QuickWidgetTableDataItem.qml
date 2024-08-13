import QtQuick 
import QCatGrayQuick 
import "../../"

CatTableViewDelegateBase {
    id: root
    delegate: CatTableViewItemBase {
        datamodel: root.datamodel
        columnIndex: root.columnIndex
        rowIndex: index
        clip: true
        border.color: ProjectObject.lineColor
        border.width: 1
        color: ProjectObject.defaultRectangleColor
        Text {
           anchors.fill: parent
           verticalAlignment: Text.AlignVCenter
           horizontalAlignment: Text.AlignHCenter
           text: datamodel.getStruct(columnIndex).data[datamodel.headerTableData[rowIndex]]
           color: ProjectObject.defaultTextColor
           font.pixelSize: 16
        }
    }

}
