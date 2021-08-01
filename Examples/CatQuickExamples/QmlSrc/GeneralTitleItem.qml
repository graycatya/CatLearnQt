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
        anchors.right: parent.right
        anchors.rightMargin: 20
        spacing: 0
        /*Rectangle {
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
        }*/

        Rectangle {
            Layout.fillWidth: true
            Layout.minimumWidth: win10titleitem.width - 76
            Layout.fillHeight: true
            color: "transparent"
        }


        RowLayout {
            id: functionLayout
            Layout.preferredWidth: 76
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignVCenter

            spacing: 15
            CatButtonImage {
                id: stylebutton
                Layout.preferredWidth: 16
                Layout.preferredHeight: 16
                Layout.alignment: Qt.AlignVCenter
                btnImgNormal: ProjectObject.getCurrentResourcePath() + "style_gray.svg"
                btnImgHovered: ProjectObject.getCurrentResourcePath() + "style_white.svg"
                btnImgPressed: ProjectObject.getCurrentResourcePath() + "style_blue.svg"
                btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "style_gray.svg"
                CatPopup {
                    id: stylepopup
                    anchors.top: stylebutton.bottom
                    backgroundWidth: 100
                    backgroundHeight: 200
                    barColor: ProjectObject.catPopupColor
                    dropshadowColor: ProjectObject.catPopupdropshadowColor

                    contentItem: ListView {
                        id: stylelistview
                        anchors.fill: parent

                        anchors.topMargin: 10
                        anchors.bottomMargin: 10
                        anchors.leftMargin: 7
                        anchors.rightMargin: 7
                        model: ProjectObject.themes

                        boundsBehavior:Flickable.StopAtBounds

                        clip: true
                        spacing: 10


                        delegate: Item {
                            width: 85
                            height: 85
                            Rectangle {
                                id: stylerect
                                anchors.fill: parent
                                anchors.margins: 5
                                color: model.Stylecolor

                                radius: 5

                                border.color: ProjectObject.styleRectBorderColor
                                border.width: 0
                            }
                            DropShadow {
                                anchors.fill: stylerect
                                horizontalOffset: 0
                                verticalOffset: 0
                                radius: 8.0
                                samples: 18
                                color: ProjectObject.catPopupdropshadowColor
                                source: stylerect
                            }

                            MouseArea {
                                id: mousea
                                anchors.fill: parent
                                hoverEnabled: true
                                cursorShape: Qt.PointingHandCursor

                                onClicked: {
                                    ProjectObject.currentTheme = index
                                    stylerect.border.width = 2
                                }

                                onEntered: {
                                    if(ProjectObject.currentTheme !== index)
                                    {
                                        stylerect.border.width = 1;
                                    }
                                }

                                onExited: {
                                    if(ProjectObject.currentTheme !== index)
                                    {
                                        stylerect.border.width = 0;
                                    }

                                }
                            }

                            Component.onCompleted: {
                                ProjectObject.updateCurrentThemeed.connect(function(){
                                    if(ProjectObject.currentTheme === index)
                                    {
                                        stylerect.border.width = 2
                                    } else {
                                        stylerect.border.width = 0
                                    }
                                });
                                if(ProjectObject.currentTheme === index)
                                {
                                    stylerect.border.width = 2
                                }
                            }
                        }

                        //orientation:ListView.Horizontal
                    }

                }

                onClicked: {
                    stylepopup.show();
                }

            }
            CatButtonImage {
                id: languagebutton
                Layout.preferredWidth: 16
                Layout.preferredHeight: 16
                Layout.alignment: Qt.AlignVCenter
                btnImgNormal: ProjectObject.getCurrentResourcePath() + "language_gray.svg"
                btnImgHovered: ProjectObject.getCurrentResourcePath() + "language_white.svg"
                btnImgPressed: ProjectObject.getCurrentResourcePath() + "language_blue.svg"
                btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "language_gray.svg"
            }
            CatButtonImage {
                id: settingbutton
                Layout.preferredWidth: 16
                Layout.preferredHeight: 16
                Layout.alignment: Qt.AlignVCenter
                btnImgNormal: ProjectObject.getCurrentResourcePath() + "setting_gray.svg"
                btnImgHovered: ProjectObject.getCurrentResourcePath() + "setting_white.svg"
                btnImgPressed: ProjectObject.getCurrentResourcePath() + "setting_blue.svg"
                btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "setting_gray.svg"
            }
        }

    }
}
