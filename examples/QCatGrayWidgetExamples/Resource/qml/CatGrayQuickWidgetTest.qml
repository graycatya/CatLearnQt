import QtQuick 2.12

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

    onUpdateStyle: function(index) {
        console.log("onUpdateStyle: " + index)
        StyleConfig.currentTheme = index;
    }
}
