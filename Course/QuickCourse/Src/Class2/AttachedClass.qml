import QtQuick 2.12

Item {

    ListView {
        anchors.fill: parent

        model: 4
        spacing: 10

        delegate: Item {
            width: 100; height: 30
            Rectangle {
                width: 100; height: 30
                color: ListView.isCurrentItem ? "red" : "yellow"
            }
        }

        currentIndex: 1
    }

    /*
        附加信号处理器
        <ArrachingType>.on<SignalName>
    */
    Component.onCompleted: {
        console.log("Attached test component")
    }
}

