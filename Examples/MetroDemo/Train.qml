import QtQuick 2.12 

import "qrc:/CustomControl"

ImageMove {
    id: train
    width: 835; height: 52
    property bool just: true

    color: "transparent"
    source: "qrc:/png/train1.png"
    state: train.just ? "lefttoright" : "righttoleft"
    animation_running: true
    animation_duration: 4000
    onJustChanged: {

        train.animation_running = false 
        train.state = train.just ? "lefttoright" : "righttoleft"
        train.animation_running = true
    }

    onVisibleChanged: {
        if (train.visible == true)
        {
            train.animation_running = true
        } else
        {
            train.animation_running = false
        }
    }
}
