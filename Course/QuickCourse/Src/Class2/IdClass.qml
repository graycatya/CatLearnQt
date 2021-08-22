import QtQuick 2.12

Item {

    Rectangle {
        anchors.fill: parent
        color: "gray"
        Column {
            anchors.fill: parent
            Text {
                id: text1
                text: "GrayCatQt"
            }

            Text {
                // 将id: text1 的text绑定到这个Text
                text: text1.text
            }
        }
    }

}
