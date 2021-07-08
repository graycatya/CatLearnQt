import QtQuick 2.12
import QtQml 2.12
import QtQuick.Layouts 1.12
import "../CatButton"
import "../CatBasics"
import "./CalendarRelyon"

Rectangle {
    id: root
    property color backdropColor: "#2C2C2C"
    property color titleColor: "#4C4C4C"
    property color titleTextColor: "#FFFFFF"
    property string textFontFamily: "Ubuntu"

    property alias preiousYearButton: previousYear
    property alias lastMonthButton: lastMonth
    property alias nextMonthButton: nextMonth
    property alias nextYearButton: nextYear

    property date calendarDate: { new Date() }

    signal previousYearClicked()
    signal lastMonthClicked()
    signal nextMonthClicked()
    signal nextYearClicked()

    implicitWidth: 350
    implicitHeight: 350

    radius: 5

    color: root.backdropColor

    CatRectangle {
        id: functionItem
        anchors.top: root.top
        anchors.left: root.left
        anchors.right: root.right

        implicitHeight: 40

        backdropRadius: root.radius
        leftBottomRound: false
        rightBottomRound: false
        leftTopRound: root.radius === 0 ? false : true
        rightTopRound: root.radius === 0 ? false : true

        backdropColor: root.titleColor

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
    }

    function clicklastMonth()
    {
        let year = calendarDate.getFullYear()
        let month = calendarDate.getMonth() - 1
        let date = calendarDate.getDate()
        calendarDate = new Date(year, month, date)
        yaermonth.text = getTitleYearMonth();
        console.log("lastMonthClicked")
    }

    function clicknextMonth()
    {
        let year = calendarDate.getFullYear()
        let month = calendarDate.getMonth() + 1
        let date = calendarDate.getDate()
        calendarDate = new Date(year, month, date)
        yaermonth.text = getTitleYearMonth();
        console.log("nextMonthClicked")
    }

    function clicknextYear()
    {
        let year = calendarDate.getFullYear() + 1
        let month = calendarDate.getMonth()
        let date = calendarDate.getDate()
        calendarDate = new Date(year, month, date)
        yaermonth.text = getTitleYearMonth();
    }

    function getTitleYearMonth()
    {
        return qsTr("%1 %2").arg(getEnMonth(calendarDate.getMonth())).arg(calendarDate.getFullYear())
    }

    function getEnMonth(month)
    {
        let month_toEn = [qsTr("January"), qsTr("February"), qsTr("March"), qsTr("April"),
                          qsTr("May"), qsTr("June"), qsTr("July"), qsTr("August"),
                          qsTr("September"), qsTr("October"), qsTr("November"), qsTr("December")];

        return month_toEn[month];
    }

    function initCalendar()
    {

    }

    Component.onCompleted: {
        yaermonth.text = getTitleYearMonth();
    }

}
