pragma Singleton
import QtQuick 2.12
import QtQml 2.12

QtObject {
    id: styleconfig
    objectName: "styleconfig"

    property int currentTheme: 0
    property color backColor: "#fbfbfb"
    property color textColor: "#4b4642"
    property color fpsgradient0Color: "#9B9898"
    property color fpsgradient1Color: "#4E4E4E"

    // table style
    property color tableviewItem_borderColor: "#D3D9D9";
    property color tableviewItem_backColor: "#343434";

    property ListModel themes: ListModel {
        ListElement {
            name: "CatWhite"
            backColor: "#fbfbfb"
            textColor: "#4b4642"
            fpsgradient0Color: "#9B9898"
            fpsgradient1Color: "#4E4E4E"
        }
        ListElement {
            name: "CatGray"
            backColor: "#343434"
            textColor: "#C1C1C1"
            fpsgradient0Color: "#9B9898"
            fpsgradient1Color: "#4E4E4E"
        }
    }

    signal updateCurrentThemeed();

    onCurrentThemeChanged: {
        var t = styleconfig.themes.get(currentTheme)
        styleconfig.backColor = t.backColor
        styleconfig.textColor = t.textColor
        styleconfig.fpsgradient0Color = t.fpsgradient0Color
        styleconfig.fpsgradient1Color = t.fpsgradient1Color
    }


}
