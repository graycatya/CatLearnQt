import QtQuick 2.12

Item {

    function getMonthDay(year, month)
    {
        let days = new Date(year, month, 0).getDate();
        return days
    }
}
