import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../CatGraphicalEffects"
import "../CatButton"

Item {
    id: generalinput

    property alias backgroudItem: backgrouditem
    property alias layoutRow: layoutrow
    property alias logoImage: logoiamge
    property real logoImageSize: 0
    property alias textInput: textinput
    property alias comboboxButton: comboboxbutton
    property alias mouseArea: mousearea
    property real comboboxButtonSize: 0
    property real textInputMargin: 0
    property bool hovered: false
    property bool butexited: true
    property alias textInputText: textinput.text

    MouseArea {
        id: mousearea

        anchors.fill: parent

        hoverEnabled: true

        onDoubleClicked: function(mouse){ mouse.accepted = false; }

        onPositionChanged: function(mouse){
            mouse.accepted = false
        }

        onPressed: function(mouse){
            mouse.accepted = false
        }

        onPressAndHold: function(mouse){
            mouse.accepted = false
        }

        onClicked: function(mouse){
            mouse.accepted = false
        }

        onReleased: function(mouse){
            mouse.accepted = false
        }

        onEntered: {
            butexited = false
            hovered = true
        }

        onExited: {
            butexited = true
            hovered = false
        }

        Rectangle {
            id: backgrouditem
            anchors.fill: parent

            RowLayout {
                id: layoutrow
                anchors.fill: backgrouditem
                spacing: 5

                Image {
                    id: logoiamge
                    Layout.preferredWidth: logoImageSize
                    Layout.preferredHeight: logoImageSize
                }

                TextField {
                    background: Item {
                        anchors.fill: parent
                    }
                    id: textinput
                    clip: true
                    selectByMouse: true
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.topMargin: textInputMargin
                    Layout.bottomMargin: textInputMargin
                    Layout.leftMargin: textInputMargin
                    Layout.rightMargin: textInputMargin
                }

                CatButtonImage {
                    id: comboboxbutton
                    Layout.preferredWidth: comboboxButtonSize
                    Layout.preferredHeight: comboboxButtonSize

                }
            }
        }
    }
}
