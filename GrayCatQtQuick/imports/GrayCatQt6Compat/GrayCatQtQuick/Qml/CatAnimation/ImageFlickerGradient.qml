import QtQuick

Item {
    id: root
    property alias source: image.source
    property int interval: 1000
    property alias repeat: timer.repeat
    property alias running: timer.running
    property alias visibles: image.visible
    readonly property string version: "1.0"
    state: "show"
    Image {
        id: image
        anchors.fill: parent
        visible: true
        asynchronous: true
    }
    Timer {
        id: timer
        interval: root.interval
        repeat: true
        running: true
        onTriggered: {
            if(root.state === "show")
            {
                root.state = "hide"
            } else {
                root.state = "show"
            }
        }
    }
    onVisibleChanged: {
        if (root.visible == true)
        {
            timer.running = true
        } else
        {
            timer.running = false
        }
    }

    states: [
        State {
            name: "show"
            PropertyChanges {
                target: image
                opacity: 1.0
            }
        },
        State {
            name: "hide"
            PropertyChanges {
                target: image
                opacity: 0.0
            }
        }
    ]
    transitions: [
        Transition {
            from: "show"
            to: "hide"
            PropertyAnimation {
                target: image
                property: "opacity"
                from: 1.0
                to: 0.0
                duration: root.interval
            }
        },
        Transition {
            from: "hide"
            to: "show"
            PropertyAnimation {
                target: image
                property: "opacity"
                from: 0.0
                to: 1.0
                duration: root.interval
            }
        }
    ]
}
