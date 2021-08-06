import QtQuick 2.12
import QtQuick 2.11 as Quick
import TestModel 1.0
//import TestJs 1.0
import TestJs 1.0 as TempTesJs
import "./TestJs3.js" as TestJs3

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

            TestModel0 {
                anchors.fill: parent
                anchors.margins: 50
                color: "#663333333"
                TestModel1 {
                    anchors.fill: parent
                    anchors.margins: 50
                    color: "#443333333"
                }
            }
        }

        /*CatFps {

        }*/

    }

    Component.onCompleted: {
        TempTesJs.TestJs0.testJsHello();
        TestJs3.testJs3Function();
    }
}
