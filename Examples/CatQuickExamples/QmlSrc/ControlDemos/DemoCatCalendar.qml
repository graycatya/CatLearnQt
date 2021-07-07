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
