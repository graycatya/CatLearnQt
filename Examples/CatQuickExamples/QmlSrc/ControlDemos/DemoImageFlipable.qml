import QtQuick 2.12
import GrayCatQtQuick 1.0
import "../"

Rectangle {
    id: demoimageflipable
    color: "transparent"

    ImageFlipable {
        anchors.centerIn: parent
        fronturl: ProjectObject.resourcePath +  "qt_logo.png"
        backurl: ProjectObject.resourcePath +  "qt_logo.png"
        width: 250
        height: 250
    }

}
