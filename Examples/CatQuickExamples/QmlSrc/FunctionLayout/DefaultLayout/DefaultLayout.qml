import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


Rectangle {
    id: defaultlayout
    color: "transparent"
    RowLayout {
        id: defaultRowlayout
        anchors.fill: parent
        spacing: 10

        Rectangle {
            Layout.preferredWidth: 400
            Layout.fillHeight: true
            color: "#2C2C2C"
            border.color: "#4E4E4E"
            border.width: 1
            radius: 5
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#2C2C2C"
            border.color: "#4E4E4E"
            border.width: 1
            radius: 5
        }
    }
}
