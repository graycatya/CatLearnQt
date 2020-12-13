import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    id: root;
    //width: 250; height: 200;

    Column {
        spacing: 0
        
        anchors.centerIn: parent

        RangeSlider {
            
            width: root.width;
            
            from: 0; to: 100; stepSize: 1
            first.value: 25; second.value: 75
        }
    }
}