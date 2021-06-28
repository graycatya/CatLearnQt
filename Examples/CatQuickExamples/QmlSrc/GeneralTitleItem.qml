import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import GrayCatQtQuick 1.0

Rectangle {
    id: win10titleitem
    objectName: "win10titleitem"


    color: ProjectObject.titleBackgroundColor

    RowLayout {
        spacing: 0
        Rectangle {
            id: logorectangle
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40
            color: "transparent"
            Image {
                id: logoimg
                anchors.centerIn: parent
                source: ProjectObject.getCurrentResourcePath() + "portrait.png"
                width: 20
                height: 20
            }
            DropShadow {
                anchors.fill: logoimg
                horizontalOffset: 0
                verticalOffset: 0
                radius: 5.0
                samples: 10
                color: ProjectObject.titleLogoShadowColor
                source: logoimg
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.minimumWidth: win10titleitem.width - 253 - 40
            Layout.fillHeight: true
            color: "transparent"
        }


        RowLayout {
            id: functionLayout
            Layout.preferredWidth: 76
            Layout.preferredHeight: 16
            Layout.alignment: Qt.AlignVCenter
            spacing: 15
            CatButtonImage {
                id: stylebutton
                width: 16
                height: 16
                btnImgNormal: ProjectObject.getCurrentResourcePath() + "style_gray.svg"
                btnImgHovered: ProjectObject.getCurrentResourcePath() + "style_white.svg"
                btnImgPressed: ProjectObject.getCurrentResourcePath() + "style_blue.svg"
                btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "style_gray.svg"
            }
            CatButtonImage {
                id: languagebutton
                width: 16
                height: 16
                btnImgNormal: ProjectObject.getCurrentResourcePath() + "language_gray.svg"
                btnImgHovered: ProjectObject.getCurrentResourcePath() + "language_white.svg"
                btnImgPressed: ProjectObject.getCurrentResourcePath() + "language_blue.svg"
                btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "language_gray.svg"
            }
            CatButtonImage {
                id: settingbutton
                width: 16
                height: 16
                btnImgNormal: ProjectObject.getCurrentResourcePath() + "setting_gray.svg"
                btnImgHovered: ProjectObject.getCurrentResourcePath() + "setting_white.svg"
                btnImgPressed: ProjectObject.getCurrentResourcePath() + "setting_blue.svg"
                btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "setting_gray.svg"
            }
        }

    }
}
