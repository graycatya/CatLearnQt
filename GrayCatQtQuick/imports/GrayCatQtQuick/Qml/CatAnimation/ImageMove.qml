import QtQuick 2.12

Rectangle {
    id: root 
    clip: true 
    color: "steelblue"
    width: imageroll.width 
    height: imageroll.height
    
    //anchors.centerIn: parent

    //Image元素抛出
    property alias source: imageroll.source

    //SequentialAnimation元素抛出
    property alias animation_loops: imageroll_sequential.loops 
    property alias animation_running: imageroll_sequential.running

    //PropertyAnimation元素抛出
    property int animation_duration: 4000
    property int xfrom: 0
    property int xto: 0
    property int yfrom: 0
    property int yto: 0
    state: "custom"

    Image {
        id: imageroll
        asynchronous: true

        ParallelAnimation{
            id: imageroll_sequential
            loops: Animation.Infinite
            PropertyAnimation{
                id: imageroll_propertyx
                target: imageroll 
            }
            PropertyAnimation{
                id: imageroll_propertyy
                target: imageroll 
            }
        }
    }

    states: [
        State {
            name: "lefttoright"
            PropertyChanges {
                target: imageroll_propertyx
                property: "x"
                from: -imageroll.width
                to: root.width
                duration: animation_duration
            }
            PropertyChanges {
                target: imageroll_propertyy
                property: "y"
                from: imageroll.y
                to: imageroll.y
                duration: animation_duration
            }
        },
        State {
            name: "righttoleft"
            PropertyChanges {
                target: imageroll_propertyx
                property: "x"
                from: root.width
                to: -imageroll.width
                duration: animation_duration
            }
            PropertyChanges {
                target: imageroll_propertyy
                property: "y"
                from: imageroll.y
                to: imageroll.y
                duration: animation_duration
            }
        },
        State {
            name: "uptodown"
            PropertyChanges {
                target: imageroll_propertyx
                property: "y"
                from: -imageroll.height
                to: root.height 
                duration: animation_duration
            }
            PropertyChanges {
                target: imageroll_propertyy
                property: "x"
                from: imageroll.x
                to: imageroll.x
                duration: animation_duration
            }
        },
        State {
            name: "downtoup"
            PropertyChanges {
                target: imageroll_propertyx
                property: "y"
                from: root.height
                to: -imageroll.height
                duration: animation_duration
            }
            PropertyChanges {
                target: imageroll_propertyy
                property: "x"
                from: imageroll.x
                to: imageroll.x
                duration: animation_duration
            }
        },
        State {
            name: "leftbuttomtorightup"
            PropertyChanges {
                target: imageroll_propertyx
                property: "x"
                from: -imageroll.width
                to: root.width
                duration: animation_duration
            }
            PropertyChanges {
                target: imageroll_propertyy
                property: "y"
                from: root.height
                to: -imageroll.height
                duration: animation_duration
            }
        },
        State {
            name: "leftuptorightbuttom"
            PropertyChanges {
                target: imageroll_propertyx
                property: "x"
                from: -imageroll.width
                to: root.width
                duration: animation_duration
            }
            PropertyChanges {
                target: imageroll_propertyy
                property: "y"
                from: -imageroll.height
                to: root.height
                duration: animation_duration
            }
        },
        State {
            name: "rightuptoleftbuttom"
            PropertyChanges {
                target: imageroll_propertyx
                property: "x"
                from: root.width
                to: -imageroll.width
                duration: animation_duration
            }
            PropertyChanges {
                target: imageroll_propertyy
                property: "y"
                from: root.height
                to: -imageroll.height
                duration: animation_duration
            }
        },
        State {
            name: "rightbuttomtoleftup"
            PropertyChanges {
                target: imageroll_propertyx
                property: "x"
                from: root.width
                to: -imageroll.width
                duration: animation_duration
            }
            PropertyChanges {
                target: imageroll_propertyy
                property: "y"
                from: -imageroll.height
                to: root.height
                duration: animation_duration
            }
        },
        State {
            name: "custom"
            PropertyChanges {
                target: imageroll_propertyx
                property: "x"
                from: root.xfrom
                to: root.xto
                duration: animation_duration
            }
            PropertyChanges {
                target: imageroll_propertyy
                property: "y"
                from: root.yfrom
                to: root.yto
                duration: animation_duration
            }
        }
    ]
    
}
