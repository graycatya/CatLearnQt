import QtQuick
import QCatGrayQuick
import QtQuick.Layouts

import QtQuick.Controls
import "../"

Rectangle {
    id: moreview
    anchors.fill: parent

    color: Qt.rgba(0, 0, 0, 0.4)

    property color moreViewBackColor: ProjectObject.moreViewBackColor
    property color moreViewFuncBackColor: ProjectObject.moreViewFuncBackColor
    property color buttonBackColor_default : ProjectObject.catsidecolumnitem_DefaultColor
    property color buttonBackColor_hover: ProjectObject.catsidecolumnitem_HoverColor
    property color buttonBackColor_pressed: ProjectObject.catsidecolumnitem_SelectColor
    //property color buttonTextColor: ProjectObject.defaultTextColor

    MouseArea {

        anchors.fill: parent;
        hoverEnabled: true

        onClicked: {
        }

        onWheel: {}

        onReleased: {}

        onPressed: {}

        onEntered: {}

        onExited: {}

    }

    Rectangle {
        id: morerect
        anchors.fill: parent
        anchors.topMargin: parent.height*0.1
        anchors.bottomMargin: parent.height*0.1
        anchors.leftMargin: {
            let cmargin = parent.width - 900
            if(cmargin > 100)
            {
                cmargin = 100
            }
            return (parent.width - 800 - cmargin)/2
        }
        anchors.rightMargin: {
            let cmargin = parent.width - 900
            if(cmargin > 100)
            {
                cmargin = 100
            }
            return (parent.width - 800 - cmargin)/2
        }


        // 解决button侧栏圆角问题 buttonsRect
        layer.enabled: true
        layer.effect: CatOpacityMask{
            maskSource: Rectangle{
                width: morerect.width
                height: morerect.height
                radius: 5
            }
        }
        //width: 800

        //anchors.centerIn: parent

        Item {
            id: topitem
            anchors.top: parent.top
            anchors.left: buttonsRect.right
            anchors.right: parent.right
            height: 50
            CatButtonImage {
                id: closebutton
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.topMargin: 15
                anchors.rightMargin: 15
                anchors.bottomMargin: 20
                btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "MoreClose_default.png"
                btnImgHovered: ProjectObject.getCurrentResourcePath() + "MoreClose_hover.png"
                btnImgNormal: ProjectObject.getCurrentResourcePath() + "MoreClose_default.png"
                btnImgPressed: ProjectObject.getCurrentResourcePath() + "MoreClose_hover.png"
                width: 15
                height: 15

                onClicked: {
                    moreview.visible = false;
                }
            }
        }



        radius: 5

        color: moreview.moreViewBackColor

        Rectangle {
            id: buttonsRect
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            //rightBottomRound: false
            //rightTopRound: false
            //backdropRadius: 5
            width: 200
            color: moreview.moreViewFuncBackColor
            //color: "#2F2F2F"
            ButtonGroup {
                buttons: functionLayout.children
            }
            ColumnLayout {
                id: functionLayout
                anchors.fill: parent
                anchors.margins: 20
                //spacing: 0

                CatButton {
                    id: settingbutton
                    Layout.fillWidth: true
                    Layout.preferredHeight: 36
                    checkable: true;
                    selected: true
                    background: Rectangle {
                        radius: 10
                        color: settingbutton.checked ? buttonBackColor_pressed : settingbutton.hovered ? buttonBackColor_hover : buttonBackColor_default
                        Image {
                            id: settingiamge
                            source: ProjectObject.getCurrentResourcePath() +  "Setting_default.png";
                            width: 20
                            height: 20
                            anchors.top: parent.top
                            anchors.left: parent.left
                            anchors.bottom: parent.bottom
                            anchors.topMargin: 8
                            anchors.leftMargin: 8
                            anchors.bottomMargin: 8
                        }

                        Text {
                            text: qsTr("Setting")
                            font.family: ProjectObject.fontFamily
                            font.pixelSize: 14
                            color: ProjectObject.defaultTextColor
                            verticalAlignment: Text.AlignVCenter
                            anchors.top: parent.top
                            anchors.left: settingiamge.right
                            anchors.bottom: parent.bottom
                            anchors.right: parent.right
                            anchors.leftMargin: 10
                        }
                    }

                    onCheckedChanged: {
                        if(checked)
                        {
                            moreswipeView.currentIndex = 0
                        }
                    }
                }

                CatButton {
                    id: licencebutton
                    Layout.fillWidth: true
                    Layout.preferredHeight: 36
                    checkable: true;
                    selected: true
                    background: Rectangle {
                        radius: 10
                        color: licencebutton.checked ? buttonBackColor_pressed : licencebutton.hovered ? buttonBackColor_hover : buttonBackColor_default
                        Image {
                            id: licenceiamge
                            source: ProjectObject.getCurrentResourcePath() +  "Licence_default.png";
                            width: 20
                            height: 20
                            anchors.top: parent.top
                            anchors.left: parent.left
                            anchors.bottom: parent.bottom
                            anchors.topMargin: 8
                            anchors.leftMargin: 8
                            anchors.bottomMargin: 8
                        }

                        Text {
                            text: qsTr("Licence")
                            font.family: ProjectObject.fontFamily
                            font.pixelSize: 14
                            color: ProjectObject.defaultTextColor
                            verticalAlignment: Text.AlignVCenter
                            anchors.top: parent.top
                            anchors.left: licenceiamge.right
                            anchors.bottom: parent.bottom
                            anchors.right: parent.right
                            anchors.leftMargin: 10
                        }
                    }

                    onCheckedChanged: {
                        if(checked)
                        {
                            moreswipeView.currentIndex = 1
                        }
                    }

                }

                CatButton {
                    id: aboutbutton
                    Layout.fillWidth: true
                    Layout.preferredHeight: 36
                    checkable: true;
                    selected: true
                    background: Rectangle {
                        radius: 10
                        color: aboutbutton.checked ? buttonBackColor_pressed : aboutbutton.hovered ? buttonBackColor_hover : buttonBackColor_default
                        Image {
                            id: aboutiamge
                            source: ProjectObject.getCurrentResourcePath() +  "About_default.png";
                            width: 20
                            height: 20
                            anchors.top: parent.top
                            anchors.left: parent.left
                            anchors.bottom: parent.bottom
                            anchors.topMargin: 8
                            anchors.leftMargin: 8
                            anchors.bottomMargin: 8
                        }

                        Text {
                            text: qsTr("About")
                            font.family: ProjectObject.fontFamily
                            font.pixelSize: 14
                            color: ProjectObject.defaultTextColor
                            verticalAlignment: Text.AlignVCenter
                            anchors.top: parent.top
                            anchors.left: aboutiamge.right
                            anchors.bottom: parent.bottom
                            anchors.right: parent.right
                            anchors.leftMargin: 10
                        }
                    }

                    onCheckedChanged: {
                        if(checked)
                        {
                            moreswipeView.currentIndex = 2
                        }
                    }
                }

                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
            }
        }

        SwipeView {
            id: moreswipeView
            anchors.top: topitem.bottom
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.left: buttonsRect.right
            interactive: false
            clip: true

            currentIndex: 0

            SettingItem {

            }

            LicenceItem {

            }

            AboutItem {

            }

            Component.onCompleted:{
                contentItem.highlightMoveDuration = 0       //将移动时间设为0
            }
        }

    }

    /*OpacityMask{
         anchors.centerIn: morerect
         width: morerect.width
         height: morerect.height
         source: morerect
         maskSource: Rectangle{
             width: morerect.width
             height: morerect.height
             radius: 5
         }
     }*/

    CatDropShadow {
        anchors.fill: morerect
        horizontalOffset: 0
        verticalOffset: 0
        radius: 8.0
        samples: 18
        color: ProjectObject.catPopupdropshadowColor
        source: morerect
    }

    onVisibleChanged: {
        settingbutton.checked = true;
    }
    
}
