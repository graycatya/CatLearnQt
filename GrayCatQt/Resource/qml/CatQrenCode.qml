import QtQuick 2.12
import QParentQrenCode 1.0

Item {
    id: root
    property string textcode: "graycatya"

    signal setTextCode(string str)
    Rectangle {
        id : rectroot
        width: parent.width;
        height: parent.height;
        color: "white";
        anchors.centerIn: parent
        ParentQrenCode {
            id: qrencode
            //anchors.centerIn: rectroot
            width: root.width;
            height: root.height;
            qrmode: ParentQrenCode.MODE_8;
            qrlevel: ParentQrenCode.CATLOG_LEVEL_Q;
            casesen: true;
            text: root.textcode;
        }
    }


    onWidthChanged: {
        rectroot.width = root.width;
        rectroot.height = root.height;
        qrencode.x = 10;
        qrencode.y = 10;
        qrencode.width = root.width - 10;
        qrencode.height = root.height - 10;
    }

    onHeightChanged: {
        rectroot.width = root.width;
        rectroot.height = root.height;
        qrencode.x = 10;
        qrencode.y = 10;
        qrencode.width = root.width - 10;
        qrencode.height = root.height - 10;
    }

    onSetTextCode: {
        qrencode.text = str;
    }
}
