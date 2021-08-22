import QtQuick 2.12
import QtQml 2.12
import QtQuick.Layouts 1.12
import "../CatButton"
import "../CatBasics"
import "./CalendarRelyon"

Rectangle {
    id: catcalendar
    property alias yearmonthstyle: yaermonth

    signal updateSelectCalendarDate(date selectdata)

    property color backdropColor: "#2C2C2C"
    property color titleColor: "#4C4C4C"
    property color titleTextColor: "#FFFFFF"
    property string textFontFamily: "Ubuntu"

    property alias preiousYearButton: previousYear
    property alias lastMonthButton: lastMonth
    property alias nextMonthButton: nextMonth
    property alias nextYearButton: nextYear

    property date selectCalendarDate: { new Date() }
    property date calendarDate: selectCalendarDate

    property color weekTextColor: "#FFFFFF"

    property color daybackColorNormal_NotForTheMonth: "#01000000"
    property color daybackColorHovered_NotForTheMonth: "#4C4C4C"
    property color daybackColorPressed_NotForTheMonth: "#3C3C3C"
    property color daybackColorDisbaled_NotForTheMonth: "#01000000"

    property color daybackColorNormal_ThatVeryDay: "#01000000"
    property color daybackColorHovered_ThatVeryDay: "#01000000"
    property color daybackColorPressed_ThatVeryDay: "#01000000"
    property color daybackColorDisbaled_ThatVeryDay: "#01000000"

    property color daybackColorNormal_TheSameMonth: "#01000000"
    property color daybackColorHovered_TheSameMonth: "#4C4C4C"
    property color daybackColorPressed_TheSameMonth: "#3C3C3C"
    property color daybackColorDisbaled_TheSameMonth: "#01000000"

    property color daybackColorNormal_Selectday: "#4C4C4C"
    property color daybackColorHovered_Selectday: "#4C4C4C"
    property color daybackColorPressed_Selectday: "#4C4C4C"
    property color daybackColorDisbaled_Selectday: "#4C4C4C"

    property int daybackWidthNormal_NotForTheMonth: 0
    property int daybackWidthHovered_NotForTheMonth: 0
    property int daybackWidthPressed_NotForTheMonth: 0
    property int daybackWidthDisbaled_NotForTheMonth: 0

    property int daybackWidthNormal_ThatVeryDay: 0
    property int daybackWidthHovered_ThatVeryDay: 0
    property int daybackWidthPressed_ThatVeryDay: 0
    property int daybackWidthDisbaled_ThatVeryDay: 0

    property int daybackWidthNormal_TheSameMonth: 0
    property int daybackWidthHovered_TheSameMonth: 0
    property int daybackWidthPressed_TheSameMonth: 0
    property int daybackWidthDisbaled_TheSameMonth: 0

    property int daybackWidthNormal_Selectday: 0
    property int daybackWidthHovered_Selectday: 0
    property int daybackWidthPressed_Selectday: 0
    property int daybackWidthDisbaled_Selectday: 0

    property color dayBorderColorNormal_NotForTheMonth: "transparent"
    property color dayBorderColorHovered_NotForTheMonth: "transparent"
    property color dayBorderColorPressed_NotForTheMonth: "transparent"
    property color dayBorderColorDisbaled_NotForTheMonth: "transparent"

    property color dayBorderColorNormal_ThatVeryDay: "transparent"
    property color dayBorderColorHovered_ThatVeryDay: "transparent"
    property color dayBorderColorPressed_ThatVeryDay: "transparent"
    property color dayBorderColorDisbaled_ThatVeryDay: "transparent"

    property color dayBorderColorNormal_TheSameMonth: "transparent"
    property color dayBorderColorHovered_TheSameMonth: "transparent"
    property color dayBorderColorPressed_TheSameMonth: "transparent"
    property color dayBorderColorDisbaled_TheSameMonth: "transparent"

    property color dayBorderColorNormal_Selectday: "transparent"
    property color dayBorderColorHovered_Selectday: "transparent"
    property color dayBorderColorPressed_Selectday: "transparent"
    property color dayBorderColorDisbaled_Selectday: "transparent"

    property color dayTextColorNormal_NotForTheMonth: "#666666"
    property color dayTextColorHovered_NotForTheMonth: "#666666"
    property color dayTextColorPressed_NotForTheMonth: "#666666"
    property color dayTextColorDisbaled_NotForTheMonth: "#666666"

    property color dayTextColorNormal_ThatVeryDay: "#19A0FA"
    property color dayTextColorHovered_ThatVeryDay: "#19A0FA"
    property color dayTextColorPressed_ThatVeryDay: "#19A0FA"
    property color dayTextColorDisbaled_ThatVeryDay: "#19A0FA"

    property color dayTextColorNormal_TheSameMonth: "#FFFFFF"
    property color dayTextColorHovered_TheSameMonth: "#FFFFFF"
    property color dayTextColorPressed_TheSameMonth: "#FFFFFF"
    property color dayTextColorDisbaled_TheSameMonth: "#FFFFFF"

    property color dayTextColorNormal_Selectday: "#FFFFFF"
    property color dayTextColorHovered_Selectday: "#FFFFFF"
    property color dayTextColorPressed_Selectday: "#FFFFFF"
    property color dayTextColorDisbaled_Selectday: "#FFFFFF"

    signal previousYearClicked()
    signal lastMonthClicked()
    signal nextMonthClicked()
    signal nextYearClicked()

    implicitWidth: 350
    implicitHeight: 350

    radius: 5

    color: catcalendar.backdropColor

    CatRectangle {
        id: functionItem
        anchors.top: catcalendar.top
        anchors.left: catcalendar.left
        anchors.right: catcalendar.right

        implicitHeight: 40

        backdropRadius: catcalendar.radius
        leftBottomRound: false
        rightBottomRound: false
        leftTopRound: catcalendar.radius === 0 ? false : true
        rightTopRound: catcalendar.radius === 0 ? false : true

        backdropColor: catcalendar.titleColor

        CatButtonImage {
            id: previousYear
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 5
            width: 25
            height: 25
            onClicked: {
                clickpreviousYear();
            }
        }

        CatButtonImage {
            id: lastMonth
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: previousYear.right
            anchors.leftMargin: 0
            width: 25
            height: 25
            onClicked: {
                clicklastMonth()
            }
        }

        CatButtonImage {
            id: nextMonth
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: nextYear.left
            anchors.rightMargin: 0
            width: 25
            height: 25
            onClicked: {
                clicknextMonth()
            }
        }

        CatButtonImage {
            id: nextYear
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 5
            width: 25
            height: 25
            onClicked: {
                clicknextYear()
            }
        }

        Text {
            id: yaermonth
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: lastMonth.right
            anchors.right: nextMonth.left
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 18
            font.family: textFontFamily
            color: titleTextColor

        }

    }

    Item {
        width: 280
        height: 280
        anchors.top: functionItem.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 15

        /*CatWeek {
            id: weekItem
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
        }*/

        DaysItem {
            id: daysItem
            anchors.fill: parent
        }

    }

    QtObject {
        id: datejs

        function getCurrentFullYear()
        {
            let current_date = new Date();
            return current_date.getFullYear()
        }

        function getCurrentYear()
        {
            let current_date = new Date();
            return current_date.getYear()
        }

        function getCurrentMonth()
        {
            let current_date = new Date();
            return current_date.getMonth() + 1
        }

        function getCurrentDate()
        {
            let current_date = new Date();
            return current_date.getDate();
        }

        function getWeek(year, month, day)
        {
            let date = new Date();
            date.setFullYear(year, month, day);
            return date.getDay()
        }

        function getMonthDay(year, month)
        {
            let days = new Date(year, month, 0).getDate();
            return days
        }
    }

    function clickpreviousYear()
    {
        let year = calendarDate.getFullYear() - 1
        let month = calendarDate.getMonth()
        let date = calendarDate.getDate()
        calendarDate = new Date(year, month, date)
        yaermonth.text = getTitleYearMonth();
        daysItem.updateYearMonth();
    }

    function clicklastMonth()
    {
        let year = calendarDate.getFullYear()
        let month = calendarDate.getMonth() - 1
        let date = calendarDate.getDate()
        calendarDate = new Date(year, month, date)
        yaermonth.text = getTitleYearMonth();
        daysItem.updateYearMonth();
    }

    function clicknextMonth()
    {
        let year = calendarDate.getFullYear()
        let month = calendarDate.getMonth() + 1
        let date = calendarDate.getDate()
        calendarDate = new Date(year, month, date)
        yaermonth.text = getTitleYearMonth();
        daysItem.updateYearMonth();
    }

    function clicknextYear()
    {
        let year = calendarDate.getFullYear() + 1
        let month = calendarDate.getMonth()
        let date = calendarDate.getDate()
        calendarDate = new Date(year, month, date)
        yaermonth.text = getTitleYearMonth();
        daysItem.updateYearMonth();
    }

    function getTitleYearMonth()
    {
        return qsTr("%1 %2").arg(getEnMonth(calendarDate.getMonth())).arg(calendarDate.getFullYear())
    }

    function getEnMonth(month)
    {
        let month_toEn = [qsTr("Jan."), qsTr("Feb."), qsTr("Mar."), qsTr("Apr."),
                          qsTr("May."), qsTr("Jun."), qsTr("Jul."), qsTr("Aug."),
                          qsTr("Sept."), qsTr("Oct."), qsTr("Nov."), qsTr("Dec.")];

        return month_toEn[month];
    }

    function updateEnMonth()
    {
        yaermonth.text = getTitleYearMonth();
    }

    function initCalendar()
    {

    }

    onSelectCalendarDateChanged: {
        catcalendar.calendarDate = catcalendar.selectCalendarDate;
        yaermonth.text = getTitleYearMonth();
        daysItem.updateYearMonth();
        updateSelectCalendarDate(catcalendar.selectCalendarDate);
    }

    Component.onCompleted: {
        yaermonth.text = getTitleYearMonth();
    }

}
