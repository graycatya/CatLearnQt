import QtQuick 2.12
// 导入不同版本的QtQuick库使用命名空间区分
import QtQuick 2.11 as Quick
// 导入本地qmldir库
import TestModel 1.0
//import TestJs 1.0
// 导入带有qmldir本地js库
import TestJs 1.0 as TempTesJs
// 导入js本地文件
import "./TestJs3.js" as TestJs3

// 导入远程目录
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
            // 自定义的库TestModel
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

        // 远程库模块
        /*CatFps {

        }*/

    }

    Component.onCompleted: {
        TempTesJs.TestJs0.testJsHello();
        TestJs3.testJs3Function();
    }
}
