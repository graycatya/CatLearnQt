import QtQuick 2.12 

import "qrc:/CustomControl"

Item {
    id: root
    width: 157; height: 100
    //SequentialAnimation元素抛出
    property var animation_loops: Animation.Infinite
    property bool animation_running: true
    //PropertyAnimation元素抛出
    property int animation_duration: 1500
    Image {
        id: doorleft
        x: 0; y: 0
        source: "qrc:/png/doorleft.png"
        asynchronous: true
        ParallelAnimation{
            running: animation_running
            loops: animation_loops
            PropertyAnimation{
                target: doorleft
                property: "x"
                from: 0
                to: -20
                duration: animation_duration
            }
            PropertyAnimation{
                target: doorleft
                property: "y"
                from: 0
                to: 0
                duration: animation_duration
            }
        }
    }
    Image {
        id: doorright
        x: 81; y: 0
        source: "qrc:/png/doorright.png"
        asynchronous: true
        ParallelAnimation{
            running: animation_running
            loops: animation_loops
            PropertyAnimation{
                target: doorright
                property: "x"
                from: 81
                to: 101
                duration: animation_duration
            }
            PropertyAnimation{
                target: doorright
                property: "y"
                from: 0
                to: 0
                duration: animation_duration
            }
        }
    }
    onVisibleChanged: {
        if (root.visible == true)
        {
            animation_running = true
        } else
        {
            animation_running = false
        }
    }
}
