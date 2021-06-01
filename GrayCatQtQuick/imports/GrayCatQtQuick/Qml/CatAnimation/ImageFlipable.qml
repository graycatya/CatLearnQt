import QtQuick 2.12 
 
Flipable {
    id: filpable 
    //width: image.source.width 
    //height: image.source.height
    state: "axisY"

    //property bool filpped: true 
    property int originX: filpable.width/2
    property int originY: filpable.height/2
    property int angles: 180  
    property url fronturl: ""
    property url backurl: ""
    property int from: 0
    property int to: 360
    property int duration: 4000
    property alias loops: animation.loops
    property alias running: animation.running

    front: Image { id: image; source: filpable.fronturl; anchors.centerIn: parent; asynchronous: true }
    back: Image { source: filpable.backurl; anchors.centerIn: parent; asynchronous: true }

    transform: Rotation {
        id: rotation 
        origin.x: filpable.originX
        origin.y: filpable.originY 
        axis.x: 0; axis.y: 1; axis.z: 0
        angle: 0 
    }

    states: [
        State {
            name: "axisX"
            PropertyChanges { target: rotation; axis.x: 1; axis.y: 0; axis.z: 0; angle: filpable.angles }
        },
        State {
            name: "axisY"
            PropertyChanges { target: rotation; axis.x: 0; axis.y: 1; axis.z: 0; angle: filpable.angles }
        },
        State {
            name: "axisZ"
            PropertyChanges { target: rotation; axis.x: 0; axis.y: 0; axis.z: 1; angle: filpable.angles }
        },
        State {
            name: "axisXY"
            PropertyChanges { target: rotation; axis.x: 1; axis.y: 1; axis.z: 0; angle: filpable.angles }
        },
        State {
            name: "axisXZ"
            PropertyChanges { target: rotation; axis.x: 1; axis.y: 0; axis.z: 1; angle: filpable.angles }
        },
        State {
            name: "axisYZ"
            PropertyChanges { target: rotation; axis.x: 0; axis.y: 1; axis.z: 1; angle: filpable.angles }
        }
    ]

    SequentialAnimation{
        id: animation
        loops: Animation.Infinite
        running: true
        NumberAnimation {
            target: rotation
            properties: "angle";
            from: filpable.from
            to: filpable.to
            duration: filpable.duration
        }
    }

    onVisibleChanged: {
        if (filpable.visible == true)
        {
            animation.running = true
        } else
        {
            animation.running = false
        }
    }
}
