import QtQuick 2.12
import QCatGrayQuick 1.0

Rectangle {
    id: root

    signal updateStyle(int index)

    color: StyleConfig.backColor

    Text {
        text: "test..."
        anchors.centerIn: parent
        font.pixelSize: 30
        font.bold: true
        color: StyleConfig.textColor
    }

    CatFps {
        id: catfps
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 5
        anchors.topMargin: 5
        gradient0Color: StyleConfig.fpsgradient0Color
        gradient1Color: StyleConfig.fpsgradient1Color
        width: 120
        height: 32
    }

    onUpdateStyle: function(index) {
        console.log("onUpdateStyle: " + index)
        StyleConfig.currentTheme = index;
    }
}
