pragma Singleton
import QtQuick 2.12
import QtQml 2.12

QtObject {
    id: styleconfig
    objectName: "styleconfig"

    property int currentTheme: 0
    property color backColor: "#fbfbfb"
    property color textColor: "#4b4642"

    property ListModel themes: ListModel {
        ListElement {
            name: "CatWhite"
            backColor: "#fbfbfb"
            textColor: "#4b4642"
        }
        ListElement {
            name: "CatGray"
            backColor: "#343434"
            textColor: "#C1C1C1"
        }
    }

    signal updateCurrentThemeed();

    onCurrentThemeChanged: {
        var t = styleconfig.themes.get(currentTheme)
        styleconfig.backColor = t.backColor
        styleconfig.textColor = t.textColor
    }


}
