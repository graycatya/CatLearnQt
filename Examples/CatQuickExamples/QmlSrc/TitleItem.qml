import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12
import GrayCatQtQuick 1.0

Rectangle {

    Layout.fillWidth: true
    Layout.preferredHeight: 50

    color: ProjectObject.titleBackgroundColor

    Image {
        id: logo
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 5
        anchors.leftMargin: 20
        source: {
            ProjectObject.getCurrentResourcePath() + "portrait.png"
        }
        width: 40
        height: 40

    }

    DropShadow {
        anchors.fill: logo
        horizontalOffset: 0
        verticalOffset: 0
        radius: 8.0
        samples: 16
        color: "#40999999"
        source: logo
    }

    RowLayout {
        id: rightlayout
        width: 430
        height:50
        anchors.top: parent.top
        anchors.right: parent.right
        spacing: 0
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"
        }

        RowLayout {
            id: settingsButtonLayout
            Layout.preferredWidth: 160
            Layout.fillHeight: true
            spacing: 0

            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "transparent"
            }

            CatButton {
                id: styleButton
                Layout.preferredWidth: 30
                Layout.preferredHeight: 30
                Layout.rightMargin: 20
                //Layout.right: settingButton.left
                background: Image {
                        anchors.centerIn: parent
                        source: styleButton.pressed ? (ProjectObject.getCurrentResourcePath() + "style_gray.png")
                                  : styleButton.hovered ?
                                  (ProjectObject.getCurrentResourcePath() + "style_blue.png")
                                  : (ProjectObject.getCurrentResourcePath() + "style_white.png")
                        width: 30
                        height: 30
                    }

            }

            CatButton {
                id: languageButton
                Layout.preferredWidth: 30
                Layout.preferredHeight: 30
                Layout.rightMargin: 20
                //Layout.right: settingButton.left
                background: Image {
                        anchors.centerIn: parent
                        source: languageButton.pressed ? (ProjectObject.getCurrentResourcePath() + "language_gray.png")
                                  : languageButton.hovered ?
                                  (ProjectObject.getCurrentResourcePath() + "language_blue.png")
                                  : (ProjectObject.getCurrentResourcePath() + "language_white.png")
                        width: 30
                        height: 30
                    }

            }

            CatButton {
                id: settingButton
                Layout.preferredWidth: 30
                Layout.preferredHeight: 30
                Layout.rightMargin: 20
                //Layout.right: partingLine.left
                background: Image {
                        anchors.centerIn: parent
                        source: settingButton.pressed ?
                                    (ProjectObject.getCurrentResourcePath() + "setting_gray.png")
                                  : settingButton.hovered ? (ProjectObject.getCurrentResourcePath() + "setting_blue.png")
                                  : (ProjectObject.getCurrentResourcePath() + "setting_white.png")
                        width: 30
                        height: 30
                    }
            }

            Rectangle {
                id: partingLine
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 1
                Layout.preferredHeight: 30
                //Layout.right: parent.right
                Layout.rightMargin: 10
                color: "#696969"
            }

        }

        RowLayout {
            Layout.preferredWidth: 240
            Layout.fillHeight: true
            spacing: 0
            CatButton {
                id: minimizedButton
                Layout.fillHeight: true
                Layout.preferredWidth: 80

                background: CatRectangle {
                    anchors.fill: parent
                    backdropColor: parent.pressed ? "#4D4D4D" :
                                   (parent.hovered ? "#4D4D4D" : "#01FFFFFF")
                    Image {
                        anchors.centerIn: parent
                        source: minimizedButton.hovered ?
                                    (ProjectObject.getCurrentResourcePath() + "minimal_white.png")
                                  : (ProjectObject.getCurrentResourcePath() + "minimal_gray.png")
                        width: 20
                        height: 20
                    }
                }
                onClicked: {
                    view.showMinimized()
                }
            }

            CatButton {
                id: maximizedButton
                Layout.fillHeight: true
                Layout.preferredWidth: 80
                visible: !isMaxed
                background: CatRectangle {
                    anchors.fill: parent
                    backdropColor: parent.pressed ? "#4D4D4D" :
                                   (parent.hovered ? "#4D4D4D" : "#01FFFFFF")
                    Image {
                        anchors.centerIn: parent
                        source: maximizedButton.hovered ?
                                    (ProjectObject.getCurrentResourcePath() + "max_white.png")
                                  : (ProjectObject.getCurrentResourcePath() + "max_gray.png")
                        width: 20
                        height: 20
                    }
                }
                onClicked: {
                    view.showMaximized()
                }
            }

            CatButton {
                id: normalButton
                Layout.fillHeight: true
                Layout.preferredWidth: 80
                visible: isMaxed
                background: CatRectangle {
                    anchors.fill: parent
                    backdropColor: parent.pressed ? "#4D4D4D" :
                                   (parent.hovered ? "#4D4D4D" : "#01FFFFFF")
                    Image {
                        anchors.centerIn: parent
                        source: normalButton.hovered ?
                                    (ProjectObject.getCurrentResourcePath() + "normal_white.png")
                                  : (ProjectObject.getCurrentResourcePath() + "normal_gray.png")
                        width: 20
                        height: 20
                    }
                }
                onClicked: {
                    view.showNormal()
                }
            }

            CatButton {
                id: closeedButton
                Layout.fillHeight: true
                Layout.preferredWidth: 80

                background: CatRectangle {
                    anchors.fill: parent
                    backdropColor: parent.pressed ? "#C14444" :
                                   (parent.hovered ? "#C14444" : "#01FFFFFF")
                    Image {
                        anchors.centerIn: parent
                        source: closeedButton.hovered ?
                                    (ProjectObject.getCurrentResourcePath() + "close_white.png")
                                  : (ProjectObject.getCurrentResourcePath() + "close_gray.png")
                        width: 20
                        height: 20
                    }
                }
                onClicked: {
                    view.close()
                }
            }

        }
    }

    property alias blankItem: blankItem
        Item {
            id: blankItem
            objectName: "blankItem"
            height: parent.height
            anchors {
                left: logo.left
                leftMargin: 4
                right: rightlayout.left
                top: parent.top
                topMargin: 4
                bottom: parent.bottom
            }
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
                        cursorShape = Qt.SizeAllCursor
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
