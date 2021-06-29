import QtQuick 2.12
import GrayCatQtQuick 1.0
import QParentQrenCode 1.0
import "../"

Rectangle {
    id: root
    //id: demoimageflipable
    color: "transparent"

    property string textcode: "graycatya"

    signal setTextCode(string str)
    Rectangle {
        id : rectroot
        width: 250;
        height: 250;
        color: ProjectObject.controlRectangleColor
        radius: 5
        anchors.centerIn: parent
        ParentQrenCode {
            id: qrencode
            //anchors.centerIn: rectroot
            anchors.fill: parent
            anchors.margins: 5
            qrmode: ParentQrenCode.MODE_8;
            qrlevel: ParentQrenCode.LEVEL_Q;
            casesen: true;
            text: root.textcode;
        }
    }

    onSetTextCode: {
        qrencode.text = str;
    }

}
