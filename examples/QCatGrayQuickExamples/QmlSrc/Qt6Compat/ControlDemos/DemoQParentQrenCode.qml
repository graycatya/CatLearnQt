import QtQuick
import QCatGrayQuick
import QParentQrenCode
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
            //anchors.margins: 5
            qrmode: ParentQrenCode.MODE_8;
            qrlevel: ParentQrenCode.LEVEL_Q;
            backgroundColor: ProjectObject.defaultRectangleColor
            qrencodeColor: ProjectObject.controlNameColor
            casesen: true;
            text: root.textcode;
        }
    }

    onSetTextCode: {
        qrencode.text = str;
    }

}
