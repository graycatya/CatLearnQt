import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


Rectangle {
    color: "transparent"
    Flow {
        anchors.fill: parent
        anchors.topMargin: 50
        anchors.leftMargin: 95
        anchors.rightMargin: 95
        anchors.bottomMargin: 50
        spacing: 60

        Rectangle {

            implicitWidth: 500
            implicitHeight: 200
            color: "#2C2C2C"
            radius: 30
        }

        Rectangle {
            Layout.preferredWidth: 500
            Layout.preferredHeight: 200
            color: "#2C2C2C"
            radius: 30
        }

        Rectangle {
            Layout.preferredWidth: 500
            Layout.preferredHeight: 200
            color: "#2C2C2C"
            radius: 30
        }

        Rectangle {
            Layout.preferredWidth: 500
            Layout.preferredHeight: 200
            color: "#2C2C2C"
            radius: 30
        }

        Rectangle {
            Layout.preferredWidth: 500
            Layout.preferredHeight: 200
            color: "#2C2C2C"
            radius: 30
        }
    }
}
