import QtQuick 2.12
import Class1 1.0

import "http://graycatya.gitee.io/GrayCatQtQuick/imports/GrayCatQtQuick"

Rectangle {
    width: Constants.width
    height: Constants.height

    color: Constants.backgroundColor

    CatFps {}

    Text {
        text: qsTr("Hello Class1")
        anchors.centerIn: parent
        font.family: Constants.font.family
    }
}
