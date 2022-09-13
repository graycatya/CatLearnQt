import QtQuick
import "../../CatButton"

Item {
    id: numberitem
    width: 40
    height: 40

    property date numberDate

    property color daybackColorNormal: {
        if(numberitem.notforthemonth)
        {
            return catcalendar.daybackColorNormal_NotForTheMonth
        } else if(numberitem.thatveryday)
        {
            return catcalendar.daybackColorNormal_ThatVeryDay
        } else if(numberitem.thesamemonth) {
            return catcalendar.daybackColorNormal_TheSameMonth
        } else {
            return catcalendar.daybackColorNormal_Selectday
        }
    }
    property color daybackColorHovered: {
        if(numberitem.notforthemonth)
        {
            return catcalendar.daybackColorHovered_NotForTheMonth
        } else if(numberitem.thatveryday)
        {
            return catcalendar.daybackColorHovered_ThatVeryDay
        } else if(numberitem.thesamemonth) {
            return catcalendar.daybackColorHovered_TheSameMonth
        } else {
            return catcalendar.daybackColorHovered_Selectday
        }
    }
    property color daybackColorPressed: {
        if(numberitem.notforthemonth)
        {
            return catcalendar.daybackColorPressed_NotForTheMonth
        } else if(numberitem.thatveryday)
        {
            return catcalendar.daybackColorPressed_ThatVeryDay
        } else if(numberitem.thesamemonth) {
            return catcalendar.daybackColorPressed_TheSameMonth
        } else {
            return catcalendar.daybackColorPressed_Selectday
        }
    }
    property color daybackColorDisbaled: {
        if(numberitem.notforthemonth)
        {
            return catcalendar.daybackColorDisbaled_NotForTheMonth
        } else if(numberitem.thatveryday)
        {
            return catcalendar.daybackColorDisbaled_ThatVeryDay
        } else if(numberitem.thesamemonth) {
            return catcalendar.daybackColorDisbaled_TheSameMonth
        } else {
            return catcalendar.daybackColorDisbaled_Selectday
        }
    }
    property color daybackColor: {
        if (!daybutton.enabled) {
            return numberitem.daybackColorDisbaled
        } else if (daybutton.pressed || daybutton.selected) {
            return numberitem.daybackColorPressed
        } else if (daybutton.hovered) {
            return numberitem.daybackColorHovered
        } else if (daybutton.checked) {
            return numberitem.daybackColorPressed
        } else {
            return numberitem.daybackColorNormal
        }
    }

    property int daybackWidthNormal: {
        if(numberitem.notforthemonth)
        {
            return catcalendar.daybackWidthNormal_NotForTheMonth
        } else if(numberitem.thatveryday)
        {
            return catcalendar.daybackWidthNormal_ThatVeryDay
        } else if(numberitem.thesamemonth) {
            return catcalendar.daybackWidthNormal_TheSameMonth
        } else {
            return catcalendar.daybackWidthNormal_Selectday
        }
    }
    property int daybackWidthHovered: {
        if(numberitem.notforthemonth)
        {
            return catcalendar.daybackWidthHovered_NotForTheMonth
        } else if(numberitem.thatveryday)
        {
            return catcalendar.daybackWidthHovered_ThatVeryDay
        } else if(numberitem.thesamemonth) {
            return catcalendar.daybackWidthHovered_TheSameMonth
        } else {
            return catcalendar.daybackWidthHovered_Selectday
        }
    }
    property int daybackWidthPressed: {
        if(numberitem.notforthemonth)
        {
            return catcalendar.daybackWidthPressed_NotForTheMonth
        } else if(numberitem.thatveryday)
        {
            return catcalendar.daybackWidthPressed_ThatVeryDay
        } else if(numberitem.thesamemonth) {
            return catcalendar.daybackWidthPressed_TheSameMonth
        } else {
            return catcalendar.daybackWidthPressed_Selectday
        }
    }
    property int daybackWidthDisbaled: {
        if(numberitem.notforthemonth)
        {
            return catcalendar.daybackWidthDisbaled_NotForTheMonth
        } else if(numberitem.thatveryday)
        {
            return catcalendar.daybackWidthDisbaled_ThatVeryDay
        } else if(numberitem.thesamemonth) {
            return catcalendar.daybackWidthDisbaled_TheSameMonth
        } else {
            return catcalendar.daybackWidthDisbaled_Selectday
        }
    }
    property int daybackWidth: {
        if (!daybutton.enabled) {
            return numberitem.daybackWidthDisbaled
        } else if (daybutton.pressed || daybutton.selected) {
            return numberitem.daybackWidthPressed
        } else if (daybutton.hovered) {
            return numberitem.daybackWidthHovered
        } else if (daybutton.checked) {
            return numberitem.daybackWidthPressed
        } else {
            return numberitem.daybackWidthNormal
        }
    }

    property color dayBorderColorNormal: {
        if(numberitem.notforthemonth)
        {
            return catcalendar.dayBorderColorNormal_NotForTheMonth
        } else if(numberitem.thatveryday)
        {
            return catcalendar.dayBorderColorNormal_ThatVeryDay
        } else if(numberitem.thesamemonth) {
            return catcalendar.dayBorderColorNormal_TheSameMonth
        } else {
            return catcalendar.dayBorderColorNormal_Selectday
        }
    }
    property color dayBorderColorHovered: {
        if(numberitem.notforthemonth)
        {
            return catcalendar.dayBorderColorHovered_NotForTheMonth
        } else if(numberitem.thatveryday)
        {
            return catcalendar.dayBorderColorHovered_ThatVeryDay
        } else if(numberitem.thesamemonth) {
            return catcalendar.dayBorderColorHovered_TheSameMonth
        } else {
            return catcalendar.dayBorderColorHovered_Selectday
        }
    }
    property color dayBorderColorPressed: {
        if(numberitem.notforthemonth)
        {
            return catcalendar.dayBorderColorPressed_NotForTheMonth
        } else if(numberitem.thatveryday)
        {
            return catcalendar.dayBorderColorPressed_ThatVeryDay
        } else if(numberitem.thesamemonth) {
            return catcalendar.dayBorderColorPressed_TheSameMonth
        } else {
            return catcalendar.dayBorderColorPressed_Selectday
        }
    }
    property color dayBorderColorDisbaled: {
        if(numberitem.notforthemonth)
        {
            return catcalendar.dayBorderColorDisbaled_NotForTheMonth
        } else if(numberitem.thatveryday)
        {
            return catcalendar.dayBorderColorDisbaled_ThatVeryDay
        } else if(numberitem.thesamemonth) {
            return catcalendar.dayBorderColorDisbaled_TheSameMonth
        } else {
            return catcalendar.dayBorderColorDisbaled_Selectday
        }
    }
    property color dayBorderColor: {
        if (!daybutton.enabled) {
            return numberitem.dayBorderColorDisbaled
        } else if (daybutton.pressed || daybutton.selected) {
            return numberitem.dayBorderColorPressed
        } else if (daybutton.hovered) {
            return numberitem.dayBorderColorHovered
        } else if (daybutton.checked) {
            return numberitem.dayBorderColorPressed
        } else {
            return numberitem.dayBorderColorNormal
        }
    }

    property color dayTextColorNormal: {
        if(numberitem.notforthemonth)
        {
            return catcalendar.dayTextColorNormal_NotForTheMonth
        } else if(numberitem.thatveryday)
        {
            return catcalendar.dayTextColorNormal_ThatVeryDay
        } else if(numberitem.thesamemonth) {
            return catcalendar.dayTextColorNormal_TheSameMonth
        } else {
            return catcalendar.dayTextColorNormal_Selectday
        }
    }
    property color dayTextColorHovered: {
        if(numberitem.notforthemonth)
        {
            return catcalendar.dayTextColorHovered_NotForTheMonth
        } else if(numberitem.thatveryday)
        {
            return catcalendar.dayTextColorHovered_ThatVeryDay
        } else if(numberitem.thesamemonth) {
            return catcalendar.dayTextColorHovered_TheSameMonth
        } else {
            return catcalendar.dayTextColorHovered_Selectday
        }
    }
    property color dayTextColorPressed: {
        if(numberitem.notforthemonth)
        {
            return catcalendar.dayTextColorPressed_NotForTheMonth
        } else if(numberitem.thatveryday)
        {
            return catcalendar.dayTextColorPressed_ThatVeryDay
        } else if(numberitem.thesamemonth) {
            return catcalendar.dayTextColorPressed_TheSameMonth
        } else {
            return catcalendar.dayTextColorPressed_Selectday
        }
    }
    property color dayTextColorDisbaled: {
        if(numberitem.notforthemonth)
        {
            return catcalendar.dayTextColorDisbaled_NotForTheMonth
        } else if(numberitem.thatveryday)
        {
            return catcalendar.dayTextColorDisbaled_ThatVeryDay
        } else if(numberitem.thesamemonth) {
            return catcalendar.dayTextColorDisbaled_TheSameMonth
        } else {
            return catcalendar.dayTextColorDisbaled_Selectday
        }
    }
    property color dayTextColor: {
        if (!daybutton.enabled) {
            return numberitem.dayTextColorDisbaled
        } else if (daybutton.pressed || daybutton.selected) {
            return numberitem.dayTextColorPressed
        } else if (daybutton.hovered) {
            return numberitem.dayTextColorHovered
        } else if (daybutton.checked) {
            return numberitem.dayTextColorPressed
        } else {
            return numberitem.dayTextColorNormal
        }
    }
    property string dayTextFamily: catcalendar.textFontFamily

    property int itemnumber: 0
    property date numberitemdate: new Date()
    property int day: 0
    property bool notforthemonth: true
    property bool thatveryday: false
    property bool thesamemonth: false
    property bool selectday: false

    CatButton {
        id: daybutton
        anchors.fill: parent

        background: Rectangle {
            id: dayback
            anchors.fill: parent
            radius: 20
            color: numberitem.daybackColor
            border.width: numberitem.daybackWidth
            border.color: numberitem.dayBorderColor

            Text {
                id: daytext
                anchors.fill: parent
                font.pixelSize: 14
                font.family: numberitem.dayTextFamily
                //font.bold: true
                color: numberitem.dayTextColor
                text: numberitem.day
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }

        onClicked: {
            catcalendar.selectCalendarDate = daysItem.numberitems[itemnumber].date
        }

    }

    states: [
        State {
            name: "NotForTheMonth"
            PropertyChanges {
                target: numberitem
                thatveryday: false
                thesamemonth: false
                selectday: false
                notforthemonth: true
            }
            PropertyChanges {
                target: daytext
                font.bold: false
            }
        },
        State {
            name: "ThatVeryDay"
            PropertyChanges {
                target: numberitem
                thesamemonth: false
                notforthemonth: false
                selectday: false
                thatveryday: true
            }
            PropertyChanges {
                target: daytext
                font.bold: true
            }
        },
        State {
            name: "TheSameMonth"
            PropertyChanges {
                target: numberitem
                notforthemonth: false
                thatveryday: false
                selectday: false
                thesamemonth: true
            }
            PropertyChanges {
                target: daytext
                font.bold: false
            }
        },
        State {
            name: "Selectday"
            PropertyChanges {
                target: numberitem
                notforthemonth: false
                thatveryday: false
                thesamemonth: false
                selectday: true
            }
            PropertyChanges {
                target: daytext
                font.bold: false
            }
        }
    ]

    Component.onCompleted: {
        daysItem.updateDayItem.connect(function(){
            numberitem.day = daysItem.numberitems[itemnumber].day
            numberitem.numberitemdate = daysItem.numberitems[itemnumber].date
            let date = new Date();
            if(numberitem.numberitemdate.getFullYear() === date.getFullYear()
                    && numberitem.numberitemdate.getMonth() === date.getMonth()
                    && numberitem.numberitemdate.getDate() === date.getDate())
            {
                numberitem.state = "ThatVeryDay"
            } else if(numberitem.numberitemdate.getFullYear() === catcalendar.selectCalendarDate.getFullYear()
                      && numberitem.numberitemdate.getMonth() === catcalendar.selectCalendarDate.getMonth()
                      && numberitem.numberitemdate.getDate() === catcalendar.selectCalendarDate.getDate())
            {
                numberitem.state = "Selectday"
            } else if(numberitem.numberitemdate.getFullYear() === catcalendar.calendarDate.getFullYear()
                      && numberitem.numberitemdate.getMonth() === catcalendar.calendarDate.getMonth())
            {
                numberitem.state = "TheSameMonth"
            } else {
                numberitem.state = "NotForTheMonth"
            }

        });
        if(itemnumber === 41)
        {
            daysItem.updateYearMonth();
        }
    }

}
