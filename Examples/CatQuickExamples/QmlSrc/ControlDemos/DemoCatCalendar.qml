import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12
import GrayCatQtQuick 1.0
import "../"

Rectangle {
    //id: demoimageflipable
    color: "transparent"

    CatCalendar {
        id: catcalendar
        anchors.centerIn: parent

        preiousYearButton.btnImgNormal: ProjectObject.getCurrentResourcePath() + "LeftLeftButton_default.svg"
        preiousYearButton.btnImgHovered: ProjectObject.getCurrentResourcePath() + "LeftLeftButton_gray.svg"
        preiousYearButton.btnImgPressed: ProjectObject.getCurrentResourcePath() + "LeftLeftButton_gray.svg"
        preiousYearButton.btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "LeftLeftButton_gray.svg"

        lastMonthButton.btnImgNormal: ProjectObject.getCurrentResourcePath() + "LeftButton_default.svg"
        lastMonthButton.btnImgHovered: ProjectObject.getCurrentResourcePath() + "LeftButton_gray.svg"
        lastMonthButton.btnImgPressed: ProjectObject.getCurrentResourcePath() + "LeftButton_gray.svg"
        lastMonthButton.btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "LeftButton_gray.svg"

        nextMonthButton.btnImgNormal: ProjectObject.getCurrentResourcePath() + "RightButton_default.svg"
        nextMonthButton.btnImgHovered: ProjectObject.getCurrentResourcePath() + "RightButton_gray.svg"
        nextMonthButton.btnImgPressed: ProjectObject.getCurrentResourcePath() + "RightButton_gray.svg"
        nextMonthButton.btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "RightButton_gray.svg"

        nextYearButton.btnImgNormal: ProjectObject.getCurrentResourcePath() + "RightRightButton_default.svg"
        nextYearButton.btnImgHovered: ProjectObject.getCurrentResourcePath() + "RightRightButton_gray.svg"
        nextYearButton.btnImgPressed: ProjectObject.getCurrentResourcePath() + "RightRightButton_gray.svg"
        nextYearButton.btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "RightRightButton_gray.svg"

        backdropColor: ProjectObject.calendarbackdropColor
        titleColor: ProjectObject.calendartitleColor
        titleTextColor: ProjectObject.calendartitleTextColor
        textFontFamily: ProjectObject.fontFamily

        weekTextColor: ProjectObject.calendarweekTextColor

        daybackColorNormal_NotForTheMonth: ProjectObject.calendardaybackColorNormal_NotForTheMonth
        daybackColorHovered_NotForTheMonth: ProjectObject.calendardaybackColorHovered_NotForTheMonth
        daybackColorPressed_NotForTheMonth: ProjectObject.calendardaybackColorPressed_NotForTheMonth
        daybackColorDisbaled_NotForTheMonth: ProjectObject.calendardaybackColorDisbaled_NotForTheMonth

        daybackColorNormal_ThatVeryDay: ProjectObject.calendardaybackColorNormal_ThatVeryDay
        daybackColorHovered_ThatVeryDay: ProjectObject.calendardaybackColorHovered_ThatVeryDay
        daybackColorPressed_ThatVeryDay: ProjectObject.calendardaybackColorPressed_ThatVeryDay
        daybackColorDisbaled_ThatVeryDay: ProjectObject.calendardaybackColorDisbaled_ThatVeryDay

        daybackColorNormal_TheSameMonth: ProjectObject.calendardaybackColorNormal_TheSameMonth
        daybackColorHovered_TheSameMonth: ProjectObject.calendardaybackColorHovered_TheSameMonth
        daybackColorPressed_TheSameMonth: ProjectObject.calendardaybackColorPressed_TheSameMonth
        daybackColorDisbaled_TheSameMonth: ProjectObject.calendardaybackColorDisbaled_TheSameMonth

        daybackColorNormal_Selectday: ProjectObject.calendardaybackColorNormal_Selectday
        daybackColorHovered_Selectday: ProjectObject.calendardaybackColorHovered_Selectday
        daybackColorPressed_Selectday: ProjectObject.calendardaybackColorPressed_Selectday
        daybackColorDisbaled_Selectday: ProjectObject.calendardaybackColorDisbaled_Selectday

        daybackWidthNormal_NotForTheMonth: ProjectObject.calendardaybackWidthNormal_NotForTheMonth
        daybackWidthHovered_NotForTheMonth: ProjectObject.calendardaybackWidthHovered_NotForTheMonth
        daybackWidthPressed_NotForTheMonth: ProjectObject.calendardaybackWidthPressed_NotForTheMonth
        daybackWidthDisbaled_NotForTheMonth: ProjectObject.calendardaybackWidthDisbaled_NotForTheMonth

        daybackWidthNormal_ThatVeryDay: ProjectObject.calendardaybackWidthNormal_ThatVeryDay
        daybackWidthHovered_ThatVeryDay: ProjectObject.calendardaybackWidthHovered_ThatVeryDay
        daybackWidthPressed_ThatVeryDay: ProjectObject.calendardaybackWidthPressed_ThatVeryDay
        daybackWidthDisbaled_ThatVeryDay: ProjectObject.calendardaybackWidthDisbaled_ThatVeryDay

        daybackWidthNormal_TheSameMonth: ProjectObject.calendardaybackWidthNormal_TheSameMonth
        daybackWidthHovered_TheSameMonth: ProjectObject.calendardaybackWidthHovered_TheSameMonth
        daybackWidthPressed_TheSameMonth: ProjectObject.calendardaybackWidthPressed_TheSameMonth
        daybackWidthDisbaled_TheSameMonth: ProjectObject.calendardaybackWidthDisbaled_TheSameMonth

        daybackWidthNormal_Selectday: ProjectObject.calendardaybackWidthNormal_Selectday
        daybackWidthHovered_Selectday: ProjectObject.calendardaybackWidthHovered_Selectday
        daybackWidthPressed_Selectday: ProjectObject.calendardaybackWidthPressed_Selectday
        daybackWidthDisbaled_Selectday: ProjectObject.calendardaybackWidthDisbaled_Selectday

        dayBorderColorNormal_NotForTheMonth: ProjectObject.calendardayBorderColorNormal_NotForTheMonth
        dayBorderColorHovered_NotForTheMonth: ProjectObject.calendardayBorderColorHovered_NotForTheMonth
        dayBorderColorPressed_NotForTheMonth: ProjectObject.calendardayBorderColorPressed_NotForTheMonth
        dayBorderColorDisbaled_NotForTheMonth: ProjectObject.calendardayBorderColorDisbaled_NotForTheMonth

        dayBorderColorNormal_ThatVeryDay: ProjectObject.calendardayBorderColorNormal_ThatVeryDay
        dayBorderColorHovered_ThatVeryDay: ProjectObject.calendardayBorderColorHovered_ThatVeryDay
        dayBorderColorPressed_ThatVeryDay: ProjectObject.calendardayBorderColorPressed_ThatVeryDay
        dayBorderColorDisbaled_ThatVeryDay: ProjectObject.calendardayBorderColorDisbaled_ThatVeryDay

        dayBorderColorNormal_TheSameMonth: ProjectObject.calendardayBorderColorNormal_TheSameMonth
        dayBorderColorHovered_TheSameMonth: ProjectObject.calendardayBorderColorHovered_TheSameMonth
        dayBorderColorPressed_TheSameMonth: ProjectObject.calendardayBorderColorPressed_TheSameMonth
        dayBorderColorDisbaled_TheSameMonth: ProjectObject.calendardayBorderColorDisbaled_TheSameMonth

        dayBorderColorNormal_Selectday: ProjectObject.calendardayBorderColorNormal_Selectday
        dayBorderColorHovered_Selectday: ProjectObject.calendardayBorderColorHovered_Selectday
        dayBorderColorPressed_Selectday: ProjectObject.calendardayBorderColorPressed_Selectday
        dayBorderColorDisbaled_Selectday: ProjectObject.calendardayBorderColorDisbaled_Selectday

        dayTextColorNormal_NotForTheMonth: ProjectObject.calendardayTextColorNormal_NotForTheMonth
        dayTextColorHovered_NotForTheMonth: ProjectObject.calendardayTextColorHovered_NotForTheMonth
        dayTextColorPressed_NotForTheMonth: ProjectObject.calendardayTextColorPressed_NotForTheMonth
        dayTextColorDisbaled_NotForTheMonth: ProjectObject.calendardayTextColorDisbaled_NotForTheMonth

        dayTextColorNormal_ThatVeryDay: ProjectObject.calendardayTextColorNormal_ThatVeryDay
        dayTextColorHovered_ThatVeryDay: ProjectObject.calendardayTextColorHovered_ThatVeryDay
        dayTextColorPressed_ThatVeryDay: ProjectObject.calendardayTextColorPressed_ThatVeryDay
        dayTextColorDisbaled_ThatVeryDay: ProjectObject.calendardayTextColorDisbaled_ThatVeryDay

        dayTextColorNormal_TheSameMonth: ProjectObject.calendardayTextColorNormal_TheSameMonth
        dayTextColorHovered_TheSameMonth: ProjectObject.calendardayTextColorHovered_TheSameMonth
        dayTextColorPressed_TheSameMonth: ProjectObject.calendardayTextColorPressed_TheSameMonth
        dayTextColorDisbaled_TheSameMonth: ProjectObject.calendardayTextColorDisbaled_TheSameMonth

        dayTextColorNormal_Selectday: ProjectObject.calendardayTextColorNormal_Selectday
        dayTextColorHovered_Selectday: ProjectObject.calendardayTextColorHovered_Selectday
        dayTextColorPressed_Selectday: ProjectObject.calendardayTextColorPressed_Selectday
        dayTextColorDisbaled_Selectday: ProjectObject.calendardayTextColorDisbaled_Selectday
    }

    DropShadow {
        anchors.fill: catcalendar
        horizontalOffset: 0
        verticalOffset: 0
        radius: 10.0
        samples: 16
        color: "#3FFFFFFF"
        source: catcalendar
    }
}
