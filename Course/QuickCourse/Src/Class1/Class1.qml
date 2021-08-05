import QtQuick 2.12
import QtQuick 2.11 as Quick
import TestModel 1.0

//import "http://graycatya.gitee.io/GrayCatQtQuick/imports/GrayCatQtQuick/"

Item {
    width: 800
    height: 600

    Rectangle {
        anchors.fill: parent
        color: "gray"
        Text {
            text: qsTr("QtQuick 2.12 Rectangle")
            font.pixelSize: 12
            color: "#FFFFFF"
        }

        Quick.Rectangle {
            anchors.fill: parent
            anchors.margins: 100
            color: "#99333333"
            Text {
                text: qsTr("QtQuick 2.11 as Quick Rectangle")
                font.pixelSize: 12
                color: "#FFFFFF"
            }
        }
/*
        CatFps {

        }
*/
    }
}
