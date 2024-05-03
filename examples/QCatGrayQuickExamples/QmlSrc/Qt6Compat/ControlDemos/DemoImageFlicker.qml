import QtQuick
import GrayCatQtQuick
import "../"

Rectangle {
    //id: demoimageflipable
    color: "transparent"

    ImageFlicker {
        anchors.centerIn: parent
        source: ProjectObject.resourcePath +  "qt_logo.png"
        width: 250
        height: 250
    }

}
