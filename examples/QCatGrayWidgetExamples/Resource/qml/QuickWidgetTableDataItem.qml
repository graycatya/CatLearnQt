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
           text: datamodel.getStruct(columnIndex).data[headerData[rowIndex]]
           color: StyleConfig.textColor

           font.pixelSize: 16
//           onTextChanged: {
//            console.log(text)
//           }
        }
    }

    Component.onCompleted: {
        console.log("rowIndex: " + rowIndex)
        console.log("columnIndex: " + columnIndex)
        console.log("datamodel.tabledata.length: " + datamodel.tabledata.length)

        //console.log(datamodel.getStruct(columnIndex).data["id"])
        //console.log(headerData[rowIndex])
        //console.log(datamodel.getStruct(columnIndex).data[headerData[rowIndex]])
    }
}
