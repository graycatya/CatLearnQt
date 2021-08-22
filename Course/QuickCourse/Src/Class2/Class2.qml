import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    width: 800
    height: 600

    SwipeView {
        id: view

        currentIndex: 0
        anchors.fill: parent

        IdClass {}

        PropertyClass {}

        SignalClass {}

        MethodClass {}

        AttachedClass {}

        EnumClass {}
    }

    PageIndicator {
        id: indicator

        count: view.count
        currentIndex: view.currentIndex

        anchors.bottom: view.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }


}
