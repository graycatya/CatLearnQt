import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import GrayCatQtQuick
import "../"

Item {
    //id: demoimagemove

    GridLayout {
        anchors.centerIn: parent
        width: 200
        height: 400
        rows: 4
        columns: 2

        ImageMove {
            source: ProjectObject.resourcePath + "qt_logo.png"
            width: 100
            height: 100
            imagewidth: 100
            imageheight: 100
            state: "lefttoright"
            animation_running: true
        }
        ImageMove {
            source: ProjectObject.resourcePath + "qt_logo.png"
            width: 100
            height: 100
            imagewidth: 100
            imageheight: 100
            state: "righttoleft"
            animation_running: true
        }

        ImageMove {
            source: ProjectObject.resourcePath + "qt_logo.png"
            width: 100
            height: 100
            imagewidth: 100
            imageheight: 100
            state: "uptodown"
            animation_running: true
        }
        ImageMove {
            source: ProjectObject.resourcePath + "qt_logo.png"
            width: 100
            height: 100
            imagewidth: 100
            imageheight: 100
            state: "downtoup"
            animation_running: true
        }

        ImageMove {
            source: ProjectObject.resourcePath + "qt_logo.png"
            width: 100
            height: 100
            imagewidth: 100
            imageheight: 100
            state: "leftbuttomtorightup"
            animation_running: true
        }
        ImageMove {
            source: ProjectObject.resourcePath + "qt_logo.png"
            width: 100
            height: 100
            imagewidth: 100
            imageheight: 100
            state: "leftuptorightbuttom"
            animation_running: true
        }

        ImageMove {
            source: ProjectObject.resourcePath + "qt_logo.png"
            width: 100
            height: 100
            imagewidth: 100
            imageheight: 100
            state: "rightuptoleftbuttom"
            animation_running: true
        }
        ImageMove {
            source: ProjectObject.resourcePath + "qt_logo.png"
            width: 100
            height: 100
            imagewidth: 100
            imageheight: 100
            state: "rightbuttomtoleftup"
            animation_running: true
        }
    }
}
