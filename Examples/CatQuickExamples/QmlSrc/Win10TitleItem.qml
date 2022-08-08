import QtQuick 2.12
import QtQml 2.12
import QtQml.Models 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.0
import GrayCatQtQuick 1.0
import GrayCatQtCompat 1.0

Rectangle {
    id: win10titleitem
    objectName: "win10titleitem"

    property alias blankItem: blankItem

    //color: ProjectObject.titleBackgroundColor

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
                source: ProjectObject.getCurrentResourcePath() + "CatQuickExamples.png"
                width: 20
                height: 20
            }
            CatDropShadow {
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
                backImage.sourceSize.width: 16
                backImage.sourceSize.height: 16
                Layout.preferredWidth: 16
                Layout.preferredHeight: 16
                btnImgNormal: ProjectObject.getCurrentResourcePath() + "style_gray.svg"
                btnImgHovered: ProjectObject.getCurrentResourcePath() + "style_white.svg"
                btnImgPressed: ProjectObject.getCurrentResourcePath() + "style_blue.svg"
                btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "style_gray.svg"

                CatPopup {
                    id: stylepopup
                    anchors.top: stylebutton.bottom
                    backgroundWidth: 200
                    backgroundHeight: 100
                    barColor: ProjectObject.catPopupColor
                    dropshadowColor: ProjectObject.catPopupdropshadowColor

                    contentItem: ListView {
                        id: stylelistview
                        anchors.fill: parent

                        anchors.topMargin: 7
                        anchors.bottomMargin: 7
                        anchors.leftMargin: 10
                        anchors.rightMargin: 10
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
                            CatDropShadow {
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

                        orientation:ListView.Horizontal
                    }

                }

                onClicked: {
                    stylepopup.show();
                }
                Component.onCompleted: framelessHelper.setHitTestVisible(stylebutton, true)
            }
            CatButtonImage {
                id: languagebutton
                width: 16
                height: 16
                backImage.sourceSize.width: 16
                backImage.sourceSize.height: 16
                Layout.preferredWidth: 16
                Layout.preferredHeight: 16
                btnImgNormal: ProjectObject.getCurrentResourcePath() + "language_gray.svg"
                btnImgHovered: ProjectObject.getCurrentResourcePath() + "language_white.svg"
                btnImgPressed: ProjectObject.getCurrentResourcePath() + "language_blue.svg"
                btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "language_gray.svg"

                ObjectModel {
                    id: languageModel
                }

                CatPopup {
                    id: languagepopup
                    anchors.top: languagebutton.bottom
                    backgroundWidth: 100
                    backgroundHeight: 100
                    barColor: ProjectObject.catPopupColor
                    dropshadowColor: ProjectObject.catPopupdropshadowColor
                    clip: true
                    contentItem: ListView {
                        id: languagelistview
                        anchors.fill: parent
                        spacing: 10

                        anchors.topMargin: 15
                        anchors.bottomMargin: 10
                        anchors.leftMargin: 10
                        anchors.rightMargin: 10
                        model: languageModel

                        boundsBehavior:Flickable.StopAtBounds


                    }

                    Component.onCompleted: {
                        let languages = catconfig.getAppDefineLanguages()
                        for(let i = 0; i < languages.length; i++)
                         {
                             let item = Qt.createComponent("qrc:/AppControl/LanguageItem.qml")
                             languageModel.insert(languagelistview.model.count, item.createObject(languagelistview));

                             languageModel.get(languagelistview.model.count - 1).languageNumber = i;
                             languageModel.get(languagelistview.model.count - 1).languageStr = languages[i];

                             languagelistview.positionViewAtEnd();
                         }
                         languagelistview.positionViewAtBeginning();
                    }
                }

                onClicked: {
                    languagepopup.show();
                }
                Component.onCompleted: framelessHelper.setHitTestVisible(languagebutton, true)
            }
            CatButtonImage {
                id: morebutton
                width: 16
                height: 16
                backImage.sourceSize.width: 16
                backImage.sourceSize.height: 16
                Layout.preferredWidth: 16
                Layout.preferredHeight: 16
                Layout.alignment: Qt.AlignVCenter
                btnImgNormal: ProjectObject.getCurrentResourcePath() + "More_gray.svg"
                btnImgHovered: ProjectObject.getCurrentResourcePath() + "More_white.svg"
                btnImgPressed: ProjectObject.getCurrentResourcePath() + "More_blue.svg"
                btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "More_gray.svg"

                onClicked: {
                    moreview.visible = true;
                }
                Component.onCompleted: framelessHelper.setHitTestVisible(morebutton, true)
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
                id: minimizbutton
                Layout.preferredHeight: 40
                Layout.preferredWidth: 50
                backImage.width: backImage.sourceSize.width
                backImage.height: backImage.sourceSize.height
                btnImgNormal: ProjectObject.getCurrentResourcePath() + "minimal_gray.png"
                btnImgHovered: ProjectObject.getCurrentResourcePath() + "minimal_white.png"
                btnImgPressed: ProjectObject.getCurrentResourcePath() + "minimal_white.png"
                btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "minimal_gray.png"
                backgroundColor: "transparent"
                backgroundColor_hovered: ProjectObject.titleButtonHoverColor
                backgroundColor_pressed: ProjectObject.titleButtonPressColor
                onClicked: {
                    root.showMinimized()
                }
                Component.onCompleted: framelessHelper.setHitTestVisible(minimizbutton, true)
            }
            CatButtonImage {
                id: maximizbutton
                Layout.preferredHeight: 40
                Layout.preferredWidth: 50
                visible: !((root.visibility === Window.Maximized) || (root.visibility === Window.FullScreen))
                backImage.width: backImage.sourceSize.width
                backImage.height: backImage.sourceSize.height
                btnImgNormal: ProjectObject.getCurrentResourcePath() + "max_gray.png"
                btnImgHovered: ProjectObject.getCurrentResourcePath() + "max_white.png"
                btnImgPressed: ProjectObject.getCurrentResourcePath() + "max_white.png"
                btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "max_gray.png"
                backgroundColor: "transparent"
                backgroundColor_hovered: ProjectObject.titleButtonHoverColor
                backgroundColor_pressed: ProjectObject.titleButtonPressColor
                onClicked: {
                    root.showMaximized()
                }
                Component.onCompleted: framelessHelper.setHitTestVisible(maximizbutton, true)
            }
            CatButtonImage {
                id: normalbutton
                Layout.preferredHeight: 40
                Layout.preferredWidth: 50
                visible: ((root.visibility === Window.Maximized) || (root.visibility === Window.FullScreen))
                backImage.width: backImage.sourceSize.width
                backImage.height: backImage.sourceSize.height
                btnImgNormal: ProjectObject.getCurrentResourcePath() + "normal_gray.png"
                btnImgHovered: ProjectObject.getCurrentResourcePath() + "normal_white.png"
                btnImgPressed: ProjectObject.getCurrentResourcePath() + "normal_white.png"
                btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "normal_gray.png"
                backgroundColor: "transparent"
                backgroundColor_hovered: ProjectObject.titleButtonHoverColor
                backgroundColor_pressed: ProjectObject.titleButtonPressColor
                onClicked: {
                    root.showNormal()
                }
                Component.onCompleted: framelessHelper.setHitTestVisible(normalbutton, true)
            }
            CatButtonImage {
                id: closebutton
                Layout.preferredHeight: 40
                Layout.preferredWidth: 50
                backImage.width: backImage.sourceSize.width
                backImage.height: backImage.sourceSize.height
                btnImgNormal: ProjectObject.getCurrentResourcePath() + "close_gray.png"
                btnImgHovered: ProjectObject.getCurrentResourcePath() + "close_white.png"
                btnImgPressed: ProjectObject.getCurrentResourcePath() + "close_white.png"
                btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "close_gray.png"
                backgroundColor: "transparent"
                backgroundColor_hovered: ProjectObject.titleCloseButtonHoverColor
                backgroundColor_pressed: ProjectObject.titleCloseButtonPressColor
                onClicked: {
                    root.close()
                }
                Component.onCompleted: framelessHelper.setHitTestVisible(closebutton, true)
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
            //view.setTitleItem(blankItem)
        }


        /*MouseArea {
            id: moveArea
            anchors.fill: parent
            // 悬停事件是否被处理
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
                root.x += xOffset
                root.y += yOffset
            }
        }*/
    }


    Component.onCompleted: {
        color = ProjectObject.titleBackgroundColor
        ProjectObject.updateCurrentThemeed.connect(function(){
            animation.start();
        });
    }

    PropertyAnimation  {
        id: animation
        target: win10titleitem;
        property: "color";
        from: color
        to: ProjectObject.titleBackgroundColor
        duration: ProjectObject.settingtransition ? 400 : 0
    }
}
