import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
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

        onDoubleClicked: { mouse.accepted = false; }

        onPositionChanged: {
            mouse.accepted = false
        }

        onPressed: {
            mouse.accepted = false
        }

        onPressAndHold: {
            mouse.accepted = false
        }

        onClicked: {
            mouse.accepted = false
        }

        onReleased: {
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
