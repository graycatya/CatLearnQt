import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import GrayCatQtQuick 1.0

Rectangle {
    id: win10titleitem
    objectName: "win10titleitem"

    property alias blankItem: blankItem

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

        Rectangle {
            Layout.preferredHeight: 20
            Layout.preferredWidth: 1
            Layout.leftMargin: 15
            Layout.rightMargin: 10
            color: "#696969"
        }

        RowLayout {
            id: titleButtonlayout
            Layout.preferredWidth: 150
            Layout.fillHeight: true
            spacing: 0
            CatButtonImage {
                //id: settingbutton
                Layout.preferredHeight: 40
                Layout.preferredWidth: 50
                btnImgNormal: ProjectObject.getCurrentResourcePath() + "minimal_gray.png"
                btnImgHovered: ProjectObject.getCurrentResourcePath() + "minimal_white.png"
                btnImgPressed: ProjectObject.getCurrentResourcePath() + "minimal_white.png"
                btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "minimal_gray.png"
                backgroundColor: "transparent"
                backgroundColor_hovered: "#393939"
                backgroundColor_pressed: "#4E4E4E"
                onClicked: {
                    view.showMinimized()
                }
            }
            CatButtonImage {
                //id: settingbutton
                Layout.preferredHeight: 40
                Layout.preferredWidth: 50
                visible: !isMaxed
                btnImgNormal: ProjectObject.getCurrentResourcePath() + "max_gray.png"
                btnImgHovered: ProjectObject.getCurrentResourcePath() + "max_white.png"
                btnImgPressed: ProjectObject.getCurrentResourcePath() + "max_white.png"
                btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "max_gray.png"
                backgroundColor: "transparent"
                backgroundColor_hovered: "#393939"
                backgroundColor_pressed: "#4E4E4E"
                onClicked: {
                    view.showMaximized()
                }
            }
            CatButtonImage {
                //id: settingbutton
                Layout.preferredHeight: 40
                Layout.preferredWidth: 50
                visible: isMaxed
                btnImgNormal: ProjectObject.getCurrentResourcePath() + "normal_gray.png"
                btnImgHovered: ProjectObject.getCurrentResourcePath() + "normal_white.png"
                btnImgPressed: ProjectObject.getCurrentResourcePath() + "normal_white.png"
                btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "normal_gray.png"
                backgroundColor: "transparent"
                backgroundColor_hovered: "#393939"
                backgroundColor_pressed: "#4E4E4E"
                onClicked: {
                    view.showNormal()
                }
            }
            CatButtonImage {
                //id: settingbutton
                Layout.preferredHeight: 40
                Layout.preferredWidth: 50
                btnImgNormal: ProjectObject.getCurrentResourcePath() + "close_gray.png"
                btnImgHovered: ProjectObject.getCurrentResourcePath() + "close_white.png"
                btnImgPressed: ProjectObject.getCurrentResourcePath() + "close_white.png"
                btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "close_gray.png"
                backgroundColor: "transparent"
                backgroundColor_hovered: "#C14444"
                backgroundColor_pressed: "#C15044"
                onClicked: {
                    view.close()
                }
            }
        }

    }

    Item {
        id: blankItem
        objectName: "blankItem"
        x: 0
        y: 0
        width: parent.width - 253
        height: parent.height
        Component.onCompleted: {
            view.setTitleItem(blankItem)
        }
        MouseArea {
            id: moveArea
            anchors.fill: parent
            property int lastX: 0
            property int lastY: 0
            property var control: parent //导出一个control属性，指定要拖动的目标， 默认就用parent好了。注意目标要有x和y属性并且可修改
            signal move(real xOffset, real yOffset)

            onContainsPressChanged: {

                if (containsPress) {
                    lastX = mouseX
                    lastY = mouseY
                } else {
                    cursorShape = Qt.ArrowCursor
                }
            }
            onPositionChanged: {
                if (pressed && control) {
                    if ((mouseX - lastX) !== 0 || (mouseY - lastY) !== 0)
                        moveArea.move(mouseX - lastX, mouseY - lastY)
                }
            }

            onMove: {
                view.x += xOffset
                view.y += yOffset
            }
        }
    }
}
