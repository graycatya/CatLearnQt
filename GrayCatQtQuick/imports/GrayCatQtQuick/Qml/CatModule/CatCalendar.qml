import QtQuick 2.12
import "../CatBasics"

Rectangle {
    id: root
    property color backdropColor: "#2C2C2C"
    property color titleColor: "#4C4C4C"
    implicitWidth: 350
    implicitHeight: 350

    radius: 5

    color: root.backdropColor

    CatRectangle {
        id: functionItem
        anchors.top: root.top
        anchors.left: root.left
        anchors.right: root.right

        implicitHeight: 40

        backdropRadius: root.radius
        leftBottomRound: false
        rightBottomRound: false
        leftTopRound: root.radius === 0 ? false : true
        rightTopRound: root.radius === 0 ? false : true

        backdropColor: root.titleColor

    }



    function getMonthDay(year, month)
    {
        let days = new Date(year, month, 0).getDate();
        return days
    }
}
