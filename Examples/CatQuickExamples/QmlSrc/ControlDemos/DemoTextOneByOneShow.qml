import QtQuick 2.12
import QtQuick.Layouts 1.12
import GrayCatQtQuick 1.0
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
        height: 32
    }
}
