import QtQuick 2.12

Item {
    width: 280
    height: 280

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

    function updateYearMonth(year, month)
    {

    }

    Component.onCompleted: {
        for(let i = 0; i < 42; i++)
        {
            daysmodel.append({"gridnumber": i});
            //daysGridView.model.
        }
    }
}
