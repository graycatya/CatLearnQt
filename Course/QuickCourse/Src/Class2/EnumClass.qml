import QtQuick 2.12

Item {
    id: root

    enum ItemState {
        OK,
        NO
    }

    property int itemState: EnumClass.NO

    Component.onCompleted: {
        console.log("itemState: " + root.itemState)
        root.itemState = EnumClass.OK
        console.log("itemState: " + root.itemState)
    }

}
