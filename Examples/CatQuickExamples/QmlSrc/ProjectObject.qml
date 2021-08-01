pragma Singleton //声明单例
import QtQuick 2.12
import QtQml 2.12


QtObject {
    id: projectobject
    objectName: "projectobject"

    property string fontFamily: "Ubuntu"

    property string resourcePath: "qrc:/Images/"

    property int currentTheme: 0

    property color appBackgroundColor: "#1F1F20"
    property color titleBackgroundColor: "#18181B"
    property color titleBottomWidthColor: "#000000"
    property color titleLogoShadowColor: "#FFFFFF"
    property color fpsgradient0Color: "#9B9898"
    property color fpsgradient1Color: "#4E4E4E"
    property color defaultShadowColor: "#3FFFFFFF"
    property color controlNameColor: "#FFFFFF"
    property color controlAuthorColor: "#9B9898"
    property color controlVersionColor: "#9B9898"
    property color defaultRectangleColor: "#2C2C2C"
    property color controlRectangleColor: "#2C2C2C"

    property color titleButtonHoverColor: "#393939"
    property color titleButtonPressColor: "#4E4E4E"
    property color titleCloseButtonHoverColor: "#C14444"
    property color titleCloseButtonPressColor: "#C15044"

    //日历样式
    property color calendarbackdropColor: "#2C2C2C"
    property color calendartitleColor: "#4C4C4C"
    property color calendartitleTextColor: "#FFFFFF"
    property color calendarweekTextColor: "#FFFFFF"

    property color calendardaybackColorNormal_NotForTheMonth: "#01000000"
    property color calendardaybackColorHovered_NotForTheMonth: "#4C4C4C"
    property color calendardaybackColorPressed_NotForTheMonth: "#3C3C3C"
    property color calendardaybackColorDisbaled_NotForTheMonth: "#01000000"

    property color calendardaybackColorNormal_ThatVeryDay: "#01000000"
    property color calendardaybackColorHovered_ThatVeryDay: "#01000000"
    property color calendardaybackColorPressed_ThatVeryDay: "#01000000"
    property color calendardaybackColorDisbaled_ThatVeryDay: "#01000000"

    property color calendardaybackColorNormal_TheSameMonth: "#01000000"
    property color calendardaybackColorHovered_TheSameMonth: "#4C4C4C"
    property color calendardaybackColorPressed_TheSameMonth: "#3C3C3C"
    property color calendardaybackColorDisbaled_TheSameMonth: "#01000000"

    property color calendardaybackColorNormal_Selectday: "#4C4C4C"
    property color calendardaybackColorHovered_Selectday: "#4C4C4C"
    property color calendardaybackColorPressed_Selectday: "#4C4C4C"
    property color calendardaybackColorDisbaled_Selectday: "#4C4C4C"

    property int calendardaybackWidthNormal_NotForTheMonth: 0
    property int calendardaybackWidthHovered_NotForTheMonth: 0
    property int calendardaybackWidthPressed_NotForTheMonth: 0
    property int calendardaybackWidthDisbaled_NotForTheMonth: 0

    property int calendardaybackWidthNormal_ThatVeryDay: 0
    property int calendardaybackWidthHovered_ThatVeryDay: 0
    property int calendardaybackWidthPressed_ThatVeryDay: 0
    property int calendardaybackWidthDisbaled_ThatVeryDay: 0

    property int calendardaybackWidthNormal_TheSameMonth: 0
    property int calendardaybackWidthHovered_TheSameMonth: 0
    property int calendardaybackWidthPressed_TheSameMonth: 0
    property int calendardaybackWidthDisbaled_TheSameMonth: 0

    property int calendardaybackWidthNormal_Selectday: 0
    property int calendardaybackWidthHovered_Selectday: 0
    property int calendardaybackWidthPressed_Selectday: 0
    property int calendardaybackWidthDisbaled_Selectday: 0

    property color calendardayBorderColorNormal_NotForTheMonth: "transparent"
    property color calendardayBorderColorHovered_NotForTheMonth: "transparent"
    property color calendardayBorderColorPressed_NotForTheMonth: "transparent"
    property color calendardayBorderColorDisbaled_NotForTheMonth: "transparent"

    property color calendardayBorderColorNormal_ThatVeryDay: "transparent"
    property color calendardayBorderColorHovered_ThatVeryDay: "transparent"
    property color calendardayBorderColorPressed_ThatVeryDay: "transparent"
    property color calendardayBorderColorDisbaled_ThatVeryDay: "transparent"

    property color calendardayBorderColorNormal_TheSameMonth: "transparent"
    property color calendardayBorderColorHovered_TheSameMonth: "transparent"
    property color calendardayBorderColorPressed_TheSameMonth: "transparent"
    property color calendardayBorderColorDisbaled_TheSameMonth: "transparent"

    property color calendardayBorderColorNormal_Selectday: "transparent"
    property color calendardayBorderColorHovered_Selectday: "transparent"
    property color calendardayBorderColorPressed_Selectday: "transparent"
    property color calendardayBorderColorDisbaled_Selectday: "transparent"

    property color calendardayTextColorNormal_NotForTheMonth: "#666666"
    property color calendardayTextColorHovered_NotForTheMonth: "#666666"
    property color calendardayTextColorPressed_NotForTheMonth: "#666666"
    property color calendardayTextColorDisbaled_NotForTheMonth: "#666666"

    property color calendardayTextColorNormal_ThatVeryDay: "#19A0FA"
    property color calendardayTextColorHovered_ThatVeryDay: "#19A0FA"
    property color calendardayTextColorPressed_ThatVeryDay: "#19A0FA"
    property color calendardayTextColorDisbaled_ThatVeryDay: "#19A0FA"

    property color calendardayTextColorNormal_TheSameMonth: "#FFFFFF"
    property color calendardayTextColorHovered_TheSameMonth: "#FFFFFF"
    property color calendardayTextColorPressed_TheSameMonth: "#FFFFFF"
    property color calendardayTextColorDisbaled_TheSameMonth: "#FFFFFF"

    property color calendardayTextColorNormal_Selectday: "#FFFFFF"
    property color calendardayTextColorHovered_Selectday: "#FFFFFF"
    property color calendardayTextColorPressed_Selectday: "#FFFFFF"
    property color calendardayTextColorDisbaled_Selectday: "#FFFFFF"

    property color democatsidecolumnback_color: "#3C3C3C"
    property color sideitemrectangleback_color: "#2C2C2C"
    property color catsidecolumnitem_SelectColor: "#3C3C3C"
    property color catsidecolumnitem_HoverColor: "#4C4C4C"
    property color catsidecolumnitem_DefaultColor: "transparent"
    property color catsidecolumnitem_FunctionColor: "#FFFFFF"

    property color switchbuttonback_DefaultColor: "#9B9898"
    property color switchbuttonback_CheckColor: "#4E4E4E"
    property color switchbuttonCircle_Color: "#C4C4C4"


    property color catPopupColor: "#2C2C2C"
    property color catPopupdropshadowColor: "#63FFFFFF"
    property color styleRectBorderColor: "#999999"

    property color defaultButton_DefaultColor: "#414141"
    property color defaultButton_HoverColor: "#414141"
    property color defaultButton_PressColor: "#414141"
    property color defaultButtonBorder_DefaultColor: "#1171AE"


    signal updateCurrentThemeed();

    onCurrentThemeChanged: {
        var t = projectobject.themes.get(currentTheme)

        projectobject.appBackgroundColor = t.appBackgroundColor
        projectobject.titleBackgroundColor = t.titleBackgroundColor
        projectobject.titleBottomWidthColor = t.titleBackgroundColor
        projectobject.titleLogoShadowColor = t.titleLogoShadowColor
        projectobject.fpsgradient0Color = t.fpsgradient0Color
        projectobject.fpsgradient1Color = t.fpsgradient1Color
        projectobject.defaultShadowColor = t.defaultShadowColor
        projectobject.controlNameColor = t.controlNameColor
        projectobject.controlAuthorColor = t.controlAuthorColor
        projectobject.controlVersionColor= t.controlVersionColor
        projectobject.defaultRectangleColor = t.defaultRectangleColor
        projectobject.controlRectangleColor = t.controlRectangleColor


        projectobject.titleButtonHoverColor = t.titleButtonHoverColor
        projectobject.titleButtonPressColor = t.titleButtonPressColor
        projectobject.titleCloseButtonHoverColor = t.titleCloseButtonHoverColor
        projectobject.titleCloseButtonPressColor = t.titleCloseButtonPressColor

        // 日历样式
        projectobject.calendarbackdropColor = t.calendarbackdropColor
        projectobject.calendartitleColor = t.calendartitleColor
        projectobject.calendartitleTextColor = t.calendartitleTextColor
        projectobject.calendarweekTextColor = t.calendarweekTextColor

        projectobject.calendardaybackColorNormal_NotForTheMonth = t.calendardaybackColorNormal_NotForTheMonth
        projectobject.calendardaybackColorHovered_NotForTheMonth = t.calendardaybackColorHovered_NotForTheMonth
        projectobject.calendardaybackColorPressed_NotForTheMonth = t.calendardaybackColorPressed_NotForTheMonth
        projectobject.calendardaybackColorDisbaled_NotForTheMonth = t.calendardaybackColorDisbaled_NotForTheMonth

        projectobject.calendardaybackColorNormal_ThatVeryDay = t.calendardaybackColorNormal_ThatVeryDay
        projectobject.calendardaybackColorHovered_ThatVeryDay = t.calendardaybackColorHovered_ThatVeryDay
        projectobject.calendardaybackColorPressed_ThatVeryDay = t.calendardaybackColorPressed_ThatVeryDay
        projectobject.calendardaybackColorDisbaled_ThatVeryDay = t.calendardaybackColorDisbaled_ThatVeryDay

        projectobject.calendardaybackColorNormal_TheSameMonth = t.calendardaybackColorNormal_TheSameMonth
        projectobject.calendardaybackColorHovered_TheSameMonth = t.calendardaybackColorHovered_TheSameMonth
        projectobject.calendardaybackColorPressed_TheSameMonth = t.calendardaybackColorPressed_TheSameMonth
        projectobject.calendardaybackColorDisbaled_TheSameMonth = t.calendardaybackColorDisbaled_TheSameMonth

        projectobject.calendardaybackColorNormal_Selectday = t.calendardaybackColorNormal_Selectday
        projectobject.calendardaybackColorHovered_Selectday = t.calendardaybackColorHovered_Selectday
        projectobject.calendardaybackColorPressed_Selectday = t.calendardaybackColorPressed_Selectday
        projectobject.calendardaybackColorDisbaled_Selectday = t.calendardaybackColorDisbaled_Selectday

        projectobject.calendardaybackWidthNormal_NotForTheMonth = t.calendardaybackWidthNormal_NotForTheMonth
        projectobject.calendardaybackWidthHovered_NotForTheMonth = t.calendardaybackWidthHovered_NotForTheMonth
        projectobject.calendardaybackWidthPressed_NotForTheMonth = t.calendardaybackWidthPressed_NotForTheMonth
        projectobject.calendardaybackWidthDisbaled_NotForTheMonth = t.calendardaybackWidthDisbaled_NotForTheMonth

        projectobject.calendardaybackWidthNormal_ThatVeryDay = t.calendardaybackWidthNormal_ThatVeryDay
        projectobject.calendardaybackWidthHovered_ThatVeryDay = t.calendardaybackWidthHovered_ThatVeryDay
        projectobject.calendardaybackWidthPressed_ThatVeryDay = t.calendardaybackWidthPressed_ThatVeryDay
        projectobject.calendardaybackWidthDisbaled_ThatVeryDay = t.calendardaybackWidthDisbaled_ThatVeryDay

        projectobject.calendardaybackWidthNormal_TheSameMonth = t.calendardaybackWidthNormal_TheSameMonth
        projectobject.calendardaybackWidthHovered_TheSameMonth = t.calendardaybackWidthHovered_TheSameMonth
        projectobject.calendardaybackWidthPressed_TheSameMonth = t.calendardaybackWidthPressed_TheSameMonth
        projectobject.calendardaybackWidthDisbaled_TheSameMonth = t.calendardaybackWidthDisbaled_TheSameMonth

        projectobject.calendardaybackWidthNormal_Selectday = t.calendardaybackWidthNormal_Selectday
        projectobject.calendardaybackWidthHovered_Selectday = t.calendardaybackWidthHovered_Selectday
        projectobject.calendardaybackWidthPressed_Selectday = t.calendardaybackWidthPressed_Selectday
        projectobject.calendardaybackWidthDisbaled_Selectday = t.calendardaybackWidthDisbaled_Selectday

        projectobject.calendardayBorderColorNormal_NotForTheMonth = t.calendardayBorderColorNormal_NotForTheMonth
        projectobject.calendardayBorderColorHovered_NotForTheMonth = t.calendardayBorderColorHovered_NotForTheMonth
        projectobject.calendardayBorderColorPressed_NotForTheMonth = t.calendardayBorderColorPressed_NotForTheMonth
        projectobject.calendardayBorderColorDisbaled_NotForTheMonth = t.calendardayBorderColorDisbaled_NotForTheMonth

        projectobject.calendardayBorderColorNormal_ThatVeryDay = t.calendardayBorderColorNormal_ThatVeryDay
        projectobject.calendardayBorderColorHovered_ThatVeryDay = t.calendardayBorderColorHovered_ThatVeryDay
        projectobject.calendardayBorderColorPressed_ThatVeryDay = t.calendardayBorderColorPressed_ThatVeryDay
        projectobject.calendardayBorderColorDisbaled_ThatVeryDay = t.calendardayBorderColorDisbaled_ThatVeryDay

        projectobject.calendardayBorderColorNormal_TheSameMonth = t.calendardayBorderColorNormal_TheSameMonth
        projectobject.calendardayBorderColorHovered_TheSameMonth = t.calendardayBorderColorHovered_TheSameMonth
        projectobject.calendardayBorderColorPressed_TheSameMonth = t.calendardayBorderColorPressed_TheSameMonth
        projectobject.calendardayBorderColorDisbaled_TheSameMonth = t.calendardayBorderColorDisbaled_TheSameMonth

        projectobject.calendardayBorderColorNormal_Selectday = t.calendardayBorderColorNormal_Selectday
        projectobject.calendardayBorderColorHovered_Selectday = t.calendardayBorderColorHovered_Selectday
        projectobject.calendardayBorderColorPressed_Selectday = t.calendardayBorderColorPressed_Selectday
        projectobject.calendardayBorderColorDisbaled_Selectday = t.calendardayBorderColorDisbaled_Selectday

        projectobject.calendardayTextColorNormal_NotForTheMonth = t.calendardayTextColorNormal_NotForTheMonth
        projectobject.calendardayTextColorHovered_NotForTheMonth = t.calendardayTextColorHovered_NotForTheMonth
        projectobject.calendardayTextColorPressed_NotForTheMonth = t.calendardayTextColorPressed_NotForTheMonth
        projectobject.calendardayTextColorDisbaled_NotForTheMonth = t.calendardayTextColorDisbaled_NotForTheMonth

        projectobject.calendardayTextColorNormal_ThatVeryDay = t.calendardayTextColorNormal_ThatVeryDay
        projectobject.calendardayTextColorHovered_ThatVeryDay = t.calendardayTextColorHovered_ThatVeryDay
        projectobject.calendardayTextColorPressed_ThatVeryDay = t.calendardayTextColorPressed_ThatVeryDay
        projectobject.calendardayTextColorDisbaled_ThatVeryDay = t.calendardayTextColorDisbaled_ThatVeryDay

        projectobject.calendardayTextColorNormal_TheSameMonth = t.calendardayTextColorNormal_TheSameMonth
        projectobject.calendardayTextColorHovered_TheSameMonth = t.calendardayTextColorHovered_TheSameMonth
        projectobject.calendardayTextColorPressed_TheSameMonth = t.calendardayTextColorPressed_TheSameMonth
        projectobject.calendardayTextColorDisbaled_TheSameMonth = t.calendardayTextColorDisbaled_TheSameMonth

        projectobject.calendardayTextColorNormal_Selectday = t.calendardayTextColorNormal_Selectday
        projectobject.calendardayTextColorHovered_Selectday = t.calendardayTextColorHovered_Selectday
        projectobject.calendardayTextColorPressed_Selectday = t.calendardayTextColorPressed_Selectday
        projectobject.calendardayTextColorDisbaled_Selectday = t.calendardayTextColorDisbaled_Selectday

        projectobject.democatsidecolumnback_color = t.democatsidecolumnback_color
        projectobject.sideitemrectangleback_color = t.sideitemrectangleback_color
        projectobject.catsidecolumnitem_SelectColor = t.catsidecolumnitem_SelectColor
        projectobject.catsidecolumnitem_HoverColor = t.catsidecolumnitem_HoverColor
        projectobject.catsidecolumnitem_DefaultColor = t.catsidecolumnitem_DefaultColor
        projectobject.catsidecolumnitem_FunctionColor = t.catsidecolumnitem_FunctionColor

        projectobject.switchbuttonback_DefaultColor = t.switchbuttonback_DefaultColor
        projectobject.switchbuttonback_CheckColor = t.switchbuttonback_CheckColor
        projectobject.switchbuttonCircle_Color = t.switchbuttonCircle_Color

        projectobject.catPopupColor = t.catPopupColor
        projectobject.catPopupdropshadowColor = t.catPopupdropshadowColor

        projectobject.defaultButton_DefaultColor = t.defaultButton_DefaultColor
        projectobject.defaultButton_HoverColor = t.defaultButton_HoverColor
        projectobject.defaultButton_PressColor = t.defaultButton_PressColor
        projectobject.defaultButtonBorder_DefaultColor = t.defaultButtonBorder_DefaultColor
        catconfig.setValue("Style", currentTheme);
        updateCurrentThemeed();
    }

    property ListModel themes: ListModel {
        ListElement {
            name: "Black"
            Stylecolor: "#000000"
            appBackgroundColor: "#1F1F20"
            titleBackgroundColor: "#18181B"
            titleBottomWidthColor: "#000000"
            titleLogoShadowColor: "#3FFFFFFF"
            fpsgradient0Color: "#9B9898"
            fpsgradient1Color: "#4E4E4E"
            defaultShadowColor: "#3FFFFFFF"
            controlNameColor: "#FFFFFF"
            controlAuthorColor: "#9B9898"
            controlVersionColor: "#9B9898"
            controlRectangleColor: "#2C2C2C"
            defaultRectangleColor: "#2C2C2C"

            titleButtonHoverColor: "#393939"
            titleButtonPressColor: "#4E4E4E"
            titleCloseButtonHoverColor: "#C14444"
            titleCloseButtonPressColor: "#C15044"


            // 日历样式
            calendarbackdropColor: "#2C2C2C"
            calendartitleColor: "#4C4C4C"
            calendartitleTextColor: "#FFFFFF"
            calendarweekTextColor: "#FFFFFF"

            calendardaybackColorNormal_NotForTheMonth: "#01000000"
            calendardaybackColorHovered_NotForTheMonth: "#4C4C4C"
            calendardaybackColorPressed_NotForTheMonth: "#3C3C3C"
            calendardaybackColorDisbaled_NotForTheMonth: "#01000000"

            calendardaybackColorNormal_ThatVeryDay: "#01000000"
            calendardaybackColorHovered_ThatVeryDay: "#01000000"
            calendardaybackColorPressed_ThatVeryDay: "#01000000"
            calendardaybackColorDisbaled_ThatVeryDay: "#01000000"

            calendardaybackColorNormal_TheSameMonth: "#01000000"
            calendardaybackColorHovered_TheSameMonth: "#4C4C4C"
            calendardaybackColorPressed_TheSameMonth: "#3C3C3C"
            calendardaybackColorDisbaled_TheSameMonth: "#01000000"

            calendardaybackColorNormal_Selectday: "#4C4C4C"
            calendardaybackColorHovered_Selectday: "#4C4C4C"
            calendardaybackColorPressed_Selectday: "#4C4C4C"
            calendardaybackColorDisbaled_Selectday: "#4C4C4C"

            calendardaybackWidthNormal_NotForTheMonth: 0
            calendardaybackWidthHovered_NotForTheMonth: 0
            calendardaybackWidthPressed_NotForTheMonth: 0
            calendardaybackWidthDisbaled_NotForTheMonth: 0

            calendardaybackWidthNormal_ThatVeryDay: 0
            calendardaybackWidthHovered_ThatVeryDay: 0
            calendardaybackWidthPressed_ThatVeryDay: 0
            calendardaybackWidthDisbaled_ThatVeryDay: 0

            calendardaybackWidthNormal_TheSameMonth: 0
            calendardaybackWidthHovered_TheSameMonth: 0
            calendardaybackWidthPressed_TheSameMonth: 0
            calendardaybackWidthDisbaled_TheSameMonth: 0

            calendardaybackWidthNormal_Selectday: 0
            calendardaybackWidthHovered_Selectday: 0
            calendardaybackWidthPressed_Selectday: 0
            calendardaybackWidthDisbaled_Selectday: 0

            calendardayBorderColorNormal_NotForTheMonth: "transparent"
            calendardayBorderColorHovered_NotForTheMonth: "transparent"
            calendardayBorderColorPressed_NotForTheMonth: "transparent"
            calendardayBorderColorDisbaled_NotForTheMonth: "transparent"

            calendardayBorderColorNormal_ThatVeryDay: "transparent"
            calendardayBorderColorHovered_ThatVeryDay: "transparent"
            calendardayBorderColorPressed_ThatVeryDay: "transparent"
            calendardayBorderColorDisbaled_ThatVeryDay: "transparent"

            calendardayBorderColorNormal_TheSameMonth: "transparent"
            calendardayBorderColorHovered_TheSameMonth: "transparent"
            calendardayBorderColorPressed_TheSameMonth: "transparent"
            calendardayBorderColorDisbaled_TheSameMonth: "transparent"

            calendardayBorderColorNormal_Selectday: "transparent"
            calendardayBorderColorHovered_Selectday: "transparent"
            calendardayBorderColorPressed_Selectday: "transparent"
            calendardayBorderColorDisbaled_Selectday: "transparent"

            calendardayTextColorNormal_NotForTheMonth: "#666666"
            calendardayTextColorHovered_NotForTheMonth: "#666666"
            calendardayTextColorPressed_NotForTheMonth: "#666666"
            calendardayTextColorDisbaled_NotForTheMonth: "#666666"

            calendardayTextColorNormal_ThatVeryDay: "#19A0FA"
            calendardayTextColorHovered_ThatVeryDay: "#19A0FA"
            calendardayTextColorPressed_ThatVeryDay: "#19A0FA"
            calendardayTextColorDisbaled_ThatVeryDay: "#19A0FA"

            calendardayTextColorNormal_TheSameMonth: "#FFFFFF"
            calendardayTextColorHovered_TheSameMonth: "#FFFFFF"
            calendardayTextColorPressed_TheSameMonth: "#FFFFFF"
            calendardayTextColorDisbaled_TheSameMonth: "#FFFFFF"

            calendardayTextColorNormal_Selectday: "#FFFFFF"
            calendardayTextColorHovered_Selectday: "#FFFFFF"
            calendardayTextColorPressed_Selectday: "#FFFFFF"
            calendardayTextColorDisbaled_Selectday: "#FFFFFF"

            democatsidecolumnback_color: "#3C3C3C"
            sideitemrectangleback_color: "#2C2C2C"
            catsidecolumnitem_SelectColor: "#3C3C3C"
            catsidecolumnitem_HoverColor: "#4C4C4C"
            catsidecolumnitem_DefaultColor: "transparent"
            catsidecolumnitem_FunctionColor: "#FFFFFF"

            switchbuttonback_DefaultColor: "#9B9898"
            switchbuttonback_CheckColor: "#4E4E4E"
            switchbuttonCircle_Color: "#C4C4C4"

            catPopupColor: "#2C2C2C"
            catPopupdropshadowColor: "#63FFFFFF"

            defaultButton_DefaultColor: "#414141"
            defaultButton_HoverColor: "#414141"
            defaultButton_PressColor: "#414141"
            defaultButtonBorder_DefaultColor: "#1171AE"

        }
        ListElement {
            name: "White"
            Stylecolor: "#FFFFFF"
            appBackgroundColor: "#EFEFEF"
            titleBackgroundColor: "#EEEEEE"
            titleBottomWidthColor: "#FFFFFF"
            titleLogoShadowColor: "#3F000000"
            fpsgradient0Color: "#9B9898"
            fpsgradient1Color: "#4E4E4E"
            defaultShadowColor: "#3F000000"
            controlNameColor: "#333333"
            controlAuthorColor: "#666666"
            controlVersionColor: "#666666"
            controlRectangleColor: "#FFFFFF"
            defaultRectangleColor: "#FFFFFF"

            titleButtonHoverColor: "#AA999999"
            titleButtonPressColor: "#AAAAAAAA"
            titleCloseButtonHoverColor: "#C14444"
            titleCloseButtonPressColor: "#C15044"

            // 日历样式
            calendarbackdropColor: "#FFFFFF"
            calendartitleColor: "#E6E6E6"
            calendartitleTextColor: "#333333"
            calendarweekTextColor: "#333333"

            calendardaybackColorNormal_NotForTheMonth: "#01000000"
            calendardaybackColorHovered_NotForTheMonth: "#19D0FA"
            calendardaybackColorPressed_NotForTheMonth: "#19A0FA"
            calendardaybackColorDisbaled_NotForTheMonth: "#01000000"

            calendardaybackColorNormal_ThatVeryDay: "#01000000"
            calendardaybackColorHovered_ThatVeryDay: "#01000000"
            calendardaybackColorPressed_ThatVeryDay: "#01000000"
            calendardaybackColorDisbaled_ThatVeryDay: "#01000000"

            calendardaybackColorNormal_TheSameMonth: "#01000000"
            calendardaybackColorHovered_TheSameMonth: "#19D0FA"
            calendardaybackColorPressed_TheSameMonth: "#19A0FA"
            calendardaybackColorDisbaled_TheSameMonth: "#01000000"

            calendardaybackColorNormal_Selectday: "#19A0FA"
            calendardaybackColorHovered_Selectday: "#19A0FA"
            calendardaybackColorPressed_Selectday: "#19A0FA"
            calendardaybackColorDisbaled_Selectday: "#19A0FA"

            calendardaybackWidthNormal_NotForTheMonth: 0
            calendardaybackWidthHovered_NotForTheMonth: 0
            calendardaybackWidthPressed_NotForTheMonth: 0
            calendardaybackWidthDisbaled_NotForTheMonth: 0

            calendardaybackWidthNormal_ThatVeryDay: 0
            calendardaybackWidthHovered_ThatVeryDay: 0
            calendardaybackWidthPressed_ThatVeryDay: 0
            calendardaybackWidthDisbaled_ThatVeryDay: 0

            calendardaybackWidthNormal_TheSameMonth: 0
            calendardaybackWidthHovered_TheSameMonth: 0
            calendardaybackWidthPressed_TheSameMonth: 0
            calendardaybackWidthDisbaled_TheSameMonth: 0

            calendardaybackWidthNormal_Selectday: 0
            calendardaybackWidthHovered_Selectday: 0
            calendardaybackWidthPressed_Selectday: 0
            calendardaybackWidthDisbaled_Selectday: 0

            calendardayBorderColorNormal_NotForTheMonth: "transparent"
            calendardayBorderColorHovered_NotForTheMonth: "transparent"
            calendardayBorderColorPressed_NotForTheMonth: "transparent"
            calendardayBorderColorDisbaled_NotForTheMonth: "transparent"

            calendardayBorderColorNormal_ThatVeryDay: "transparent"
            calendardayBorderColorHovered_ThatVeryDay: "transparent"
            calendardayBorderColorPressed_ThatVeryDay: "transparent"
            calendardayBorderColorDisbaled_ThatVeryDay: "transparent"

            calendardayBorderColorNormal_TheSameMonth: "transparent"
            calendardayBorderColorHovered_TheSameMonth: "transparent"
            calendardayBorderColorPressed_TheSameMonth: "transparent"
            calendardayBorderColorDisbaled_TheSameMonth: "transparent"

            calendardayBorderColorNormal_Selectday: "transparent"
            calendardayBorderColorHovered_Selectday: "transparent"
            calendardayBorderColorPressed_Selectday: "transparent"
            calendardayBorderColorDisbaled_Selectday: "transparent"

            calendardayTextColorNormal_NotForTheMonth: "#666666"
            calendardayTextColorHovered_NotForTheMonth: "#FFFFFF"
            calendardayTextColorPressed_NotForTheMonth: "#FFFFFF"
            calendardayTextColorDisbaled_NotForTheMonth: "#666666"

            calendardayTextColorNormal_ThatVeryDay: "#19A0FA"
            calendardayTextColorHovered_ThatVeryDay: "#19A0FA"
            calendardayTextColorPressed_ThatVeryDay: "#19A0FA"
            calendardayTextColorDisbaled_ThatVeryDay: "#19A0FA"

            calendardayTextColorNormal_TheSameMonth: "#000000"
            calendardayTextColorHovered_TheSameMonth: "#FFFFFF"
            calendardayTextColorPressed_TheSameMonth: "#FFFFFF"
            calendardayTextColorDisbaled_TheSameMonth: "#000000"

            calendardayTextColorNormal_Selectday: "#FFFFFF"
            calendardayTextColorHovered_Selectday: "#FFFFFF"
            calendardayTextColorPressed_Selectday: "#FFFFFF"
            calendardayTextColorDisbaled_Selectday: "#FFFFFF"

            democatsidecolumnback_color: "#FFFFFF"
            sideitemrectangleback_color: "#EFEFEF"
            catsidecolumnitem_SelectColor: "#DDDDDD"
            catsidecolumnitem_HoverColor: "#E1E1E1"
            catsidecolumnitem_DefaultColor: "transparent"
            catsidecolumnitem_FunctionColor: "#333333"

            switchbuttonback_DefaultColor: "#EEEEEE"
            switchbuttonback_CheckColor: "#41CD52"
            switchbuttonCircle_Color: "#C4C4C4"

            catPopupColor: "#FFFFFF"
            catPopupdropshadowColor: "#63000000"

            defaultButton_DefaultColor: "#FFFFFF"
            defaultButton_HoverColor: "#FFFFFF"
            defaultButton_PressColor: "#FFFFFF"
            defaultButtonBorder_DefaultColor: "#1171AE"


        }
    }

    property var defaultControl: {
        "control": [
            {
                "name": "ImageFlipable",
                "author" : "GrayCatQt",
                "version" : "1.0",
                "logoSource": "ImageFlipable.png",
                "qmlSource": projectobject.getProjectQmlControlPath() + "DemoImageFlipable.qml",
                "libs": "default",
            },
            {
                "name": "ImageFlicker",
                "author" : "GrayCatQt",
                "version" : "1.0",
                "logoSource": "ImageFlicker.png",
                "qmlSource": projectobject.getProjectQmlControlPath() + "DemoImageFlicker.qml",
                "libs": "default",
            },
            {
                "name": "ImageFlickerGradient",
                "author" : "GrayCatQt",
                "version" : "1.0",
                "logoSource": "ImageFlickerGradient.png",
                "qmlSource": projectobject.getProjectQmlControlPath() + "DemoImageFlickerGradient.qml",
                "libs": "default",
            },
            {
                "name": "ImageMove",
                "author" : "GrayCatQt",
                "version" : "1.0",
                "logoSource": "ImageMove.png",
                "qmlSource": projectobject.getProjectQmlControlPath() + "DemoImageMove.qml",
                "libs": "default",
            },
            {
                "name": "ImageScale",
                "author" : "GrayCatQt",
                "version" : "1.0",
                "logoSource": "ImageScale.png",
                "qmlSource": projectobject.getProjectQmlControlPath() + "DemoImageScale.qml",
                "libs": "default",
            },
            {
                "name": "Marquee",
                "author" : "GrayCatQt",
                "version" : "1.0",
                "logoSource": "Marquee.png",
                "qmlSource": projectobject.getProjectQmlControlPath() + "DemoMarquee.qml",
                "libs": "default",
            },
            {
                "name": "TextOneByOneShow",
                "author" : "GrayCatQt",
                "version" : "1.0",
                "logoSource": "TextOneByOneShow.png",
                "qmlSource": projectobject.getProjectQmlControlPath() + "DemoTextOneByOneShow.qml",
                "libs": "default",
            },
            {
                "name": "CatRectangle",
                "author" : "GrayCatQt",
                "version" : "1.0",
                "logoSource": "CatRectangle.png",
                "qmlSource": projectobject.getProjectQmlControlPath() + "DemoCatRectangle.qml",
                "libs": "default",
            },
            {
                "name": "QParentQrenCode",
                "author" : "GrayCatQt",
                "version" : "1.0",
                "logoSource": "QrenCode.svg",
                "qmlSource": projectobject.getProjectQmlControlPath() + "DemoQParentQrenCode.qml",
                "libs": "default",
            },
            {
                "name": "CatCalendar",
                "author" : "GrayCatQt",
                "version" : "1.0",
                "logoSource": "CatCalendar.png",
                "qmlSource": projectobject.getProjectQmlControlPath() + "DemoCatCalendar.qml",
                "libs": "default",
            },
            {
                "name": "Image3dRotation",
                "author" : "Qt",
                "version" : "1.0",
                "logoSource": "3drotation.svg",
                "qmlSource": projectobject.getProjectQmlControlPath() + "Image3dRotation.qml",
                "libs": "quick3d",
            },
            {
                "name": "CatECharts",
                "author" : "GrayCatQt",
                "version" : "1.0",
                "logoSource": "CatECharts.png",
                "qmlSource": projectobject.getProjectQmlControlPath() + "DemoCatEchars.qml",
                "libs": "webengine",
            },
            {
                "name": "CatSideColumn",
                "author" : "GrayCatQt",
                "version" : "1.0",
                "logoSource": "CatSideColumn.png",
                "qmlSource": projectobject.getProjectQmlControlPath() + "DemoCatSideColumn.qml",
                "libs": "default",
            },
        ]
    }

    Component.onCompleted: {
        projectobject.currentTheme = 0
        console.log("themes: " + getCurrentThemesName());
    }

    /*
     * 获取当前样式名
    */
    function getCurrentThemesName()
    {
        return projectobject.themes.get(currentTheme).name
    }
    /*
     * 获取当前样式皮肤路径
    */
    function getCurrentResourcePath()
    {
        return projectobject.resourcePath +
                projectobject.themes.get(currentTheme).name +
                "/"
    }

    function getProjectQmlControlPath()
    {
        return "qrc:/ControlDemos/"
    }

}
