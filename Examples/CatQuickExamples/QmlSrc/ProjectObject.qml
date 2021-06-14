pragma Singleton //声明单例
import QtQuick 2.12


QtObject {
    id: projectobject
    objectName: "projectobject"

    property string fontFamily: "微软雅黑"

    property string resourcePath: "qrc:/Images/"

    property int currentTheme: -1

    property color appBackgroundColor: "#1F1F20"
    property color titleBackgroundColor: "#18181B"
    property color titleBottomWidthColor: "#000000"

    onCurrentThemeChanged: {
        var t = projectobject.themes.get(currentTheme)
        projectobject.appBackgroundColor = t.appBackgroundColor
        projectobject.titleBackgroundColor = t.titleBackgroundColor
        projectobject.titleBottomWidthColor = t.titleBackgroundColor
    }

    property ListModel themes: ListModel {
        ListElement {
            name: "Black"
            appBackgroundColor: "#1F1F20"
            titleBackgroundColor: "#18181B"
            titleBottomWidthColor: "#000000"

        }
    }

    Component.onCompleted: {
        projectobject.currentTheme = 0

        console.log("themes: " + getCurrentThemesName());
    }

    function getCurrentThemesName()
    {
        return projectobject.themes.get(currentTheme).name
    }

    function getCurrentResourcePath()
    {
        return projectobject.resourcePath +
                projectobject.themes.get(currentTheme).name +
                "/"
    }

}
