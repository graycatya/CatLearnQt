import QtQuick
import QtQuick.Controls
import "../"

Item {
    id: webkitLicence
    clip: true

        Text {
            anchors.fill: parent
            //textFormat: Text.RichText
            text: "SingleApplication(The MIT License)\nCatLearnQt(GPL v3)"
            wrapMode: Text.WordWrap //换行
            font.pixelSize: 24
            font.family: ProjectObject.fontFamily
            color: ProjectObject.defaultTextColor
            clip: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

        }


}
