import QtQuick 
import QCatGrayQuick 
import QtQuick.Layouts 
import "../"

Rectangle {
    id: root
    //id: demoimageflipable
    color: "transparent"


    RowLayout {
        anchors.verticalCenter: parent.verticalCenter
        //anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        //anchors.bottom: parent.bottom
        anchors.margins: 5
        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        CatButton {
            Layout.fillHeight: true
            Layout.minimumHeight: 40
            Layout.preferredWidth: 120
            background: Rectangle {
                anchors.fill: parent
                radius: 5

                color: ProjectObject.defaultButton_DefaultColor
                border.width: parent.hovered ? 1 : 0
                border.color: ProjectObject.styleRectBorderColor

                CatBasicsText {
                    anchors.fill: parent
                    font.family: ProjectObject.fontFamily
                    font.pixelSize: 14
                    color: ProjectObject.defaultTextColor
                    text: "Succeed Message"
                }
            }

            onClicked: {
                ProjectObject.messageObj.message("Succeed Message.")
            }
        }

        CatButton {

            Layout.fillHeight: true
            Layout.minimumHeight: 40
            Layout.preferredWidth: 120
            background: Rectangle {
                anchors.fill: parent
                radius: 5

                color: ProjectObject.defaultButton_DefaultColor
                border.width: parent.hovered ? 1 : 0
                border.color: ProjectObject.styleRectBorderColor

                CatBasicsText {
                    anchors.fill: parent
                    font.family: ProjectObject.fontFamily
                    font.pixelSize: 14
                    color: ProjectObject.defaultTextColor
                    text: "Warning Message"
                }
            }

            onClicked: {
                ProjectObject.messageObj.message("Warning Message. Warning Message. Warning Message.", CatMessage.Warning)
            }
        }

        CatButton {

            Layout.fillHeight: true
            Layout.minimumHeight: 40
            Layout.preferredWidth: 120
            background: Rectangle {
                anchors.fill: parent
                radius: 5

                color: ProjectObject.defaultButton_DefaultColor
                border.width: parent.hovered ? 1 : 0
                border.color: ProjectObject.styleRectBorderColor

                CatBasicsText {
                    anchors.fill: parent
                    font.family: ProjectObject.fontFamily
                    font.pixelSize: 14
                    color: ProjectObject.defaultTextColor
                    text: "Information Message"
                }
            }

            onClicked: {
                ProjectObject.messageObj.message("Information Message. Information Message. Information Message. Information Message.", CatMessage.Information)
            }
        }

        CatButton {

            Layout.fillHeight: true
            Layout.minimumHeight: 40
            Layout.preferredWidth: 120
            background: Rectangle {
                anchors.fill: parent
                radius: 5

                color: ProjectObject.defaultButton_DefaultColor
                border.width: parent.hovered ? 1 : 0
                border.color: ProjectObject.styleRectBorderColor

                CatBasicsText {
                    anchors.fill: parent
                    font.family: ProjectObject.fontFamily
                    font.pixelSize: 14
                    color: ProjectObject.defaultTextColor
                    text: "Errored Message"
                }
            }

            onClicked: {
                ProjectObject.messageObj.message("Errored Message. Errored Message. Errored Message. Errored Message. Errored Message. Errored Message.", CatMessage.Errored)
            }
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
