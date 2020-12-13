import QtQuick 2.12
import QParentQrenCode 1.0

Item {
    id: root
    property string textcode: "graycatya"

    signal setTextCode(string str)
    Rectangle {
        width: parent.width;
        height: parent.height;
        color: "white";
        ParentQrenCode {
            id: qrencode

            width: parent.width;
            height: parent.height;
            qrmode: ParentQrenCode.MODE_8;
            qrlevel: ParentQrenCode.LEVEL_Q;
            casesen: true;
            text: root.textcode;
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

        }
    }


    onWidthChanged: {
        qrencode.width = root.width;
        qrencode.height = root.height;
    }

    onHeightChanged: {
        qrencode.width = root.width;
        qrencode.height = root.height;
    }

    onSetTextCode: {
        qrencode.text = str;
    }
}
