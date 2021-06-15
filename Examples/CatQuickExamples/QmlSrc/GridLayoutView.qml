import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


Rectangle {
    color: "transparent"
    GridView {
        id: gridview
        anchors.fill: parent
        anchors.topMargin: 50
        anchors.leftMargin: 95
        anchors.rightMargin: 95
        anchors.bottomMargin: 50

        //row: 3
        //column: 2
        //model: 100
        delegate: Component {
            Rectangle {
                width: parent.width
                //anchors.fill: parent
                height: 200
                color: "#2C2C2C"
                radius: 30
            }
        }
    }

    onWidthChanged: {

    }

    Component.onCompleted: {
        /*gridview.model.insert(gridview.model.count, {})
        gridview.model.insert(gridview.model.count, {})
        gridview.model.insert(gridview.model.count, {})
        gridview.model.insert(gridview.model.count, {})
        gridview.model.insert(gridview.model.count, {})
        gridview.model.insert(gridview.model.count, {})*/
    }
}
