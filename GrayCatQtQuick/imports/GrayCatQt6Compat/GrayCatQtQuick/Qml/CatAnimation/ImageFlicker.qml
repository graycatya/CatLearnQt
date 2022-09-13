import QtQuick

Item {
    id: root 
    property alias source: image.source
    property alias interval: timer.interval
    property alias repeat: timer.repeat
    property alias running: timer.running
    property alias visibles: image.visible
    readonly property string version: "1.0"
    Image {
        id: image 
        anchors.fill: parent
        visible: true
        asynchronous: true
    }
    Timer {
        id: timer
        interval: 500
        repeat: true 
        running: true 
        onTriggered: {
            image.visible = !image.visible
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
}
