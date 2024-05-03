import QtQuick
import QtQuick.Layouts
import GrayCatQtQuick
import "../"

Item {
    TextOneByOneShow {
        anchors.centerIn: parent
        color: ProjectObject.controlNameColor
        text.font.pixelSize: 32
        text.font.family: ProjectObject.fontFamily
        text.font.bold: true
        textVar: ["H", "e", "l", "l", "o", " ", "Q", "t", "!"]
        width: 300
        height: 40
    }
}
