import QtQuick 2.12
import QtQml 2.12
import QtQuick.Layouts 1.12

Item {
    id: root
    property color weekTextColor: catcalendar.weekTextColor
    property string weekTextFontFamily: catcalendar.textFontFamily

    width: parent.width
    height: 40

    RowLayout {


        anchors.fill: parent
        spacing: 0

        Text {
            //anchors.
            id: sun
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40
            text: qsTr("Sun")
            font.pixelSize: 16
            font.family: root.weekTextFontFamily
            color: root.weekTextColor
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Text {
            //anchors.
            id: mon
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40
            text: qsTr("Mon")
            font.pixelSize: 16
            font.family: root.weekTextFontFamily
            color: root.weekTextColor
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Text {
            //anchors.
            id: tue
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40
            text: qsTr("Tue")
            font.pixelSize: 16
            font.family: root.weekTextFontFamily
            color: root.weekTextColor
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Text {
            //anchors.
            id: wed
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40
            text: qsTr("Wed")
            font.pixelSize: 16
            font.family: root.weekTextFontFamily
            color: root.weekTextColor
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Text {
            //anchors.
            id: thu
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40
            text: qsTr("Thu")
            font.pixelSize: 16
            font.family: root.weekTextFontFamily
            color: root.weekTextColor
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Text {
            //anchors.
            id: fri
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40
            text: qsTr("Fri")
            font.pixelSize: 16
            font.family: root.weekTextFontFamily
            color: root.weekTextColor
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Text {
            //anchors.
            id: sat
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40
            text: qsTr("Sat")
            font.pixelSize: 16
            font.family: root.weekTextFontFamily
            color: root.weekTextColor
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
