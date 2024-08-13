import QtQuick 2.12
import QCatGrayQuick 1.0

CatTableViewDelegateBase {
    id: root
    delegate: CatTableViewItemBase {
        datamodel: root.datamodel
        columnIndex: root.columnIndex
        rowIndex: index
        clip: true
        border.color: StyleConfig.tableviewItem_borderColor
        border.width: 1
        color: StyleConfig.tableviewItem_backColor
        Text {
           anchors.fill: parent
           verticalAlignment: Text.AlignVCenter
           horizontalAlignment: Text.AlignHCenter
           text: datamodel.getStruct(columnIndex).data[datamodel.headerTableData[rowIndex]]
           color: StyleConfig.textColor
           font.pixelSize: 16
        }
    }

}
