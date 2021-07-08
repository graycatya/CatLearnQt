import QtQuick 2.12
import "../../CatButton"

Item {
    id: numberitem
    width: 40
    height: 40

    property date numberDate
    property color daybackColor: "#01000000"
    property int daybackWidth: 0
    property color dayBorderColor: "transparent"
    property color dayTextColor: "#FFFFFF"
    property string dayTextFamily: "Ubuntu"

    property int itemnumber: 0
    property int day: 0

    CatButton {
        id: daybutton
        anchors.fill: parent

        background: Rectangle {
            id: dayback
            anchors.fill: parent
            radius: 20
            color: daybackColor
            border.width: daybackWidth
            border.color: dayBorderColor

            Text {
                id: daytext
                anchors.fill: parent
                font.pixelSize: 14
                font.family: dayTextFamily
                //font.bold: true
                color: dayTextColor
                text: itemnumber
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }

        onClicked: {

        }

    }

}
