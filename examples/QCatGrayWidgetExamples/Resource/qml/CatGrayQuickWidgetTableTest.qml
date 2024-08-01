import QtQuick 2.12
import QtQuick.Controls 2.12
import QCatGrayQuick 1.0

Rectangle {
    id: root

    signal updateStyle(int index)

    color: StyleConfig.backColor



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

    CatTableView {
        id: cattableview
        anchors.fill: parent
        anchors.topMargin: 50
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.bottomMargin: 20
        color: "red"
    }

    onUpdateStyle: function(index) {
        console.log("onUpdateStyle: " + index)
        StyleConfig.currentTheme = index;
    }
}
