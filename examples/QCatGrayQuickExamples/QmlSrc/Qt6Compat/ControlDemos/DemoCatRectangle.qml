import QtQuick
import QtQuick.Layouts
import GrayCatQtQuick
import "../"

Rectangle {
    //id: demoimageflipable
    color: "transparent"


    CatRectangle {
        id: rectangle
        anchors.centerIn: parent
        anchors.leftMargin: -50
        width: 250
        height: 250
        backdropRadius: 10
        backdropColor: ProjectObject.controlRectangleColor
        borderWidth: 2
        borderColor: ProjectObject.defaultShadowColor
        leftTopRound: lefttop.checked
        rightTopRound: righttop.checked
        leftBottomRound: leftbottom.checked
        rightBottomRound: rightbottom.checked
    }

    RowLayout {
        height: 20
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: 8

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 20
            spacing: 5
            CatButtonImage {
                id: lefttop
                checkable: true
                btnImgUrl: lefttop.checked ?
                               ProjectObject.getCurrentResourcePath() + "checkbox_true.svg"
                             : ProjectObject.getCurrentResourcePath() + "checkbox_false.svg"
                Layout.preferredWidth: 20
                Layout.preferredHeight: 20
                backImage.width: 20
                backImage.height: 20
            }

            Text {
                //Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredHeight: 20
                Layout.alignment: Qt.AlignVCenter
                font.family: ProjectObject.fontFamily
                font.pixelSize: 16
                color: ProjectObject.controlNameColor


                text: qsTr("lefttop")
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 20
            spacing: 5
            CatButtonImage {
                id: righttop
                checkable: true
                btnImgUrl: righttop.checked ?
                               ProjectObject.getCurrentResourcePath() + "checkbox_true.svg"
                             : ProjectObject.getCurrentResourcePath() + "checkbox_false.svg"
                Layout.preferredWidth: 20
                Layout.preferredHeight: 20
                backImage.width: 20
                backImage.height: 20
            }

            Text {
                //Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredHeight: 20
                Layout.alignment: Qt.AlignVCenter
                font.family: ProjectObject.fontFamily
                font.pixelSize: 16
                color: ProjectObject.controlNameColor


                text: qsTr("righttop")
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 20
            spacing: 5
            CatButtonImage {
                id: leftbottom
                checkable: true
                btnImgUrl: leftbottom.checked ?
                               ProjectObject.getCurrentResourcePath() + "checkbox_true.svg"
                             : ProjectObject.getCurrentResourcePath() + "checkbox_false.svg"
                Layout.preferredWidth: 20
                Layout.preferredHeight: 20
                backImage.width: 20
                backImage.height: 20
            }

            Text {
                //Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredHeight: 20
                Layout.alignment: Qt.AlignVCenter
                font.family: ProjectObject.fontFamily
                font.pixelSize: 16
                color: ProjectObject.controlNameColor


                text: qsTr("leftbottom")
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 20
            spacing: 5
            CatButtonImage {
                id: rightbottom
                checkable: true
                btnImgUrl: rightbottom.checked ?
                               ProjectObject.getCurrentResourcePath() + "checkbox_true.svg"
                             : ProjectObject.getCurrentResourcePath() + "checkbox_false.svg"
                Layout.preferredWidth: 20
                Layout.preferredHeight: 20
                backImage.width: 20
                backImage.height: 20
            }

            Text {
                //Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredHeight: 20
                Layout.alignment: Qt.AlignVCenter
                font.family: ProjectObject.fontFamily
                font.pixelSize: 16
                color: ProjectObject.controlNameColor


                text: qsTr("rightbottom")
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"
        }
    }

}
