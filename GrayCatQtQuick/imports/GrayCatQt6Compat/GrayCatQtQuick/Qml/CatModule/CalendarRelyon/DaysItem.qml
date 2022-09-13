import QtQuick

Item {
    width: 280
    height: 280

    signal updateDayItem()


    property var numberitems: [
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
        {
            "day": 0,
            "date": new Date()
        },
    ]


    ListModel {
        id: daysmodel
    }

    GridView {
        id: daysGridView
        anchors.fill: parent

        cellWidth: 40
        cellHeight: 40

        model: daysmodel

        delegate: NumberItem {
            itemnumber: gridnumber

        }

        header: CatWeek {

        }

        focus: true
        interactive: false

    }

    function updateYearMonth()
    {
        let date = catcalendar.calendarDate
        let week = datejs.getWeek(date.getFullYear(), date.getMonth(), 1)
        let days = datejs.getMonthDay(date.getFullYear(), date.getMonth() + 1)
        let lastmonthdays = datejs.getMonthDay(date.getFullYear(), date.getMonth())
        let nextmonthdays = datejs.getMonthDay(date.getFullYear(), date.getMonth() + 2)
        let i = 0;
        let nextdays = 1;
        if(week === 0)
        {
            for(i = 0; i < days; i++)
            {
                numberitems[7+i].day = i+1;
                numberitems[7+i].date = new Date(date.getFullYear(), date.getMonth(), i+1)
            }
            for(i = 6; i >= 0; i--)
            {
                numberitems[i].day = lastmonthdays;
                numberitems[i].date = new Date(date.getFullYear(), date.getMonth() - 1, lastmonthdays)
                lastmonthdays--;
            }

            for(i = 7 + days; i < 42; i++)
            {
                numberitems[i].day = nextdays;
                numberitems[i].date = new Date(date.getFullYear(), date.getMonth() + 1, nextdays)
                nextdays++;
            }
        } else {
            for(i = 0; i < days; i++)
            {
                numberitems[week+i].day = i+1;
                numberitems[week+i].date = new Date(date.getFullYear(), date.getMonth(), i+1)
            }
            for(i = week - 1; i >= 0; i--)
            {
                numberitems[i].day = lastmonthdays;
                numberitems[i].date = new Date(date.getFullYear(), date.getMonth() - 1, lastmonthdays)
                lastmonthdays--;
            }
            for(i = week + days; i < 42; i++)
            {
                numberitems[i].day = nextdays;
                numberitems[i].date = new Date(date.getFullYear(), date.getMonth() + 1, nextdays)
                nextdays++;
            }
        }
        updateDayItem();
        //console.log("updateyearmonth: " + week + " " + days + " Month: " + (date.getMonth()+1))
    }

    Component.onCompleted: {
        for(let i = 0; i < 42; i++)
        {
            daysmodel.append({"gridnumber": i});
        }
    }
}
