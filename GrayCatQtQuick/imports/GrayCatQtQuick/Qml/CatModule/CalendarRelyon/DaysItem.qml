import QtQuick 2.12

Item {
    width: 280
    height: 280

    GridView {
        id: daysGridView
        anchors.fill: parent

        header: CatWeek {
        }

    }

    function updateYearMonth(year, month)
    {

    }
}
