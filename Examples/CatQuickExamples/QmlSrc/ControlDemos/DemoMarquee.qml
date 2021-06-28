import QtQuick 2.12
import QtQuick.Layouts 1.12
import GrayCatQtQuick 1.0
import "../"

Rectangle {
    //id: demoimageflipable
    color: "transparent"
    GridLayout {
        anchors.centerIn: parent
        width: 300
        height: 264
        rows: 2
        columns: 2
        rowSpacing: 0
        columnSpacing: 0
        Marquee {
            text: "Hello Qt!"
            font.pixelSize: 32
            font.bold: true
            text_color: ProjectObject.controlNameColor
            font.family: ProjectObject.fontFamily
            animation_running: true
            animation_duration: 2000
            width: 150
            height: 32
            state: "lefttoright"
        }
        Marquee {
            text: "Hello Qt!"
            font.pixelSize: 32
            font.bold: true
            text_color: ProjectObject.controlNameColor
            font.family: ProjectObject.fontFamily
            animation_running: true
            animation_duration: 2000
            width: 150
            height: 32
            state: "righttoleft"
        }
        Marquee {
            text: "Hello Qt!"
            font.pixelSize: 32
            font.bold: true
            text_color: ProjectObject.controlNameColor
            font.family: ProjectObject.fontFamily
            animation_running: true
            animation_duration: 2000
            width: 150
            height: 100
            state: "uptodown"
        }
        Marquee {
            text: "Hello Qt!"
            font.pixelSize: 32
            font.bold: true
            text_color: ProjectObject.controlNameColor
            font.family: ProjectObject.fontFamily
            animation_running: true
            animation_duration: 2000
            width: 150
            height: 100
            state: "downtoup"
        }
    }

}
