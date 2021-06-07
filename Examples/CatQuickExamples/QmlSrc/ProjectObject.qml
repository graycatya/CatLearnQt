pragma Singleton //声明单例
import QtQuick 2.12


QtObject {
    id: projectobject
    objectName: "projectobject"

    property string fontFamily: "微软雅黑"

    property string resourcePath: "qrc:/Images/"

    property ListModel themes: ListModel {
        ListElement {
            name: "Black"
            titleBackgroundColor: "#18181B"
            titleBottomColor: "#000000"
        }
    }

}
