import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12
import "../../"

Rectangle {
    id: defaultlayout
    color: "transparent"

    Text {
        anchors.centerIn: parent
        text: "grid test"
        font.family: ProjectObject.fontFamily
        font.pixelSize: 20
        color: ProjectObject.defaultTextColor
        font.bold: true
    }

}
