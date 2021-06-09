import QtQuick 2.0
import GrayCatQtQuick 1.0


Rectangle {
    id: root
    width: 800
    height: 600

    CatRectangle {
        anchors.centerIn: root
        width: 200
        height: 200
        backdropColor: "gray"
        backdropRadius: 10
        borderWidth: 3
        borderColor: "red"
        clip: false
        leftBottomRound: false
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
