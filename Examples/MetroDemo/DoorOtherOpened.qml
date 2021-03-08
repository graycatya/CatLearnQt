import QtQuick 2.12

import "qrc:/CustomControl"

Item {
    //x: 1143; y: 70
    width: 124; height: 100
    Image {
        source: "qrc:/png/door.png"
        asynchronous: true
    }
    ImageFlicker {
        x: 31; y: 16
        source: "qrc:/png/forbid.png"
    }
}
