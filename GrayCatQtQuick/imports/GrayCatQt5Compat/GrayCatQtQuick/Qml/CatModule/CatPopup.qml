import QtQuick 2.12
import QtQuick.Controls 2.12
import "../CatGraphicalEffects"

Item {
    id: catpopup
    anchors.fill: parent
    property alias popupVisible: popup.visible
    property alias contentItem: popup.contentItem
    property color barColor: "#2C2C2C"
    property alias backgroundItem: background
    property real backgroundWidth: 200
    property real backgroundHeight: 160
    property color borderColor: barColor
    property real borderWidth: 0

    property color dropshadowColor: "#63FFFFFF"

    property real verticalOffset: 30


    Rectangle {
        id: bar
        visible: popup.visible
        rotation: 45
        width: verticalOffset
        height: width
        color: barColor
        border.color: borderColor

        anchors.horizontalCenter: parent.horizontalCenter

        //垂直方向上，由ToolTip的y值，决定位置
        anchors.verticalCenter: parent.bottom
        anchors.verticalCenterOffset: verticalOffset
    }
    CatDropShadow {
        anchors.fill: bar
        horizontalOffset: 0
        verticalOffset: 0
        radius: 8.0
        rotation: bar.rotation
        visible: popup.visible
        samples: 16
        color: dropshadowColor
        source: bar
    }

    Popup {
        id: popup
        width: backgroundWidth
        height: backgroundHeight
        background: Rectangle {
            color: "transparent"
            Rectangle {
                id: background
                color: barColor
                anchors.fill: parent
                anchors.margins: 5
                radius: 6
                border.color: borderColor
                border.width: borderWidth
            }
            CatDropShadow {
                anchors.fill: background
                horizontalOffset: 0
                verticalOffset: 0
                radius: 8.0
                samples: 18
                color: dropshadowColor
                source: background
            }

            Rectangle {
                //id: bar
                visible: popup.visible
                rotation: 45
                width: verticalOffset
                height: width
                color: barColor
                border.color: borderColor
                //anchors.verticalCenterOffset:

                anchors.horizontalCenter: parent.horizontalCenter

                //垂直方向上，由ToolTip的y值，决定位置
                anchors.verticalCenter: parent.top
                anchors.verticalCenterOffset: 5
            }
        }
    }


    function show() {
        popup.x = (catpopup.width - popup.width) / 2
        popup.y = catpopup.height +  catpopup.verticalOffset - 5
        popupVisible = true
    }
}
