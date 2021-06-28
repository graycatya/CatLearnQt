import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "../../ControlDemos"
import "../../"

Rectangle {
    id: demonstrationview
    property string controlname: "--------"

    Text {
        id: controlnametext
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 20
        anchors.leftMargin: 40
        text: controlname
        font.pixelSize: 26
        font.family: ProjectObject.fontFamily
        font.bold: true
        color: ProjectObject.controlNameColor
    }
    SwipeView {
        id: functionswipeview
        width: parent.width
        anchors.top: controlnametext.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 10
        anchors.leftMargin: 0
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        currentIndex: 0
        interactive: false
        spacing: 5

        DemoImageFlipable {
        }

        DemoImageFlicker {
        }

        DemoImageFlickerGradient {
        }

        clip: true
    }

    function updatedemo(demoname, index)
    {
        controlname = demoname
        catLog.debug_print("controlname: " + controlname + " index: " + index)
        functionswipeview.currentIndex = index
    }

}
