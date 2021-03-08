import QtQuick 2.12 

import "qrc:/CustomControl"
import "UiConfig.js" as Uidefine


Item {
    id: root
    width: 1366 
    height: 256 
    property int startstation: 20
    property int endstation: 0
    property int nextstation: 19
    property bool just: true
    
    Image {
        id: imagebackground 
        source: "qrc:/png/background.png"
        width: source.width 
        height: source.height 
        asynchronous: true
    }
    Image {
        x: 86; y: 19
        source: "qrc:/png/logotext.png"
        width: source.width 
        height: source.height
        asynchronous: true
    }
    ImageFlipable {
        x: 29; y: 17
        width: 45
        height: 42
        fronturl: "qrc:/png/logo.png"
        backurl: "qrc:/png/logo.png"
        state: "axisY"

    }
    Image {
        x: 25; y: 74
        source: "qrc:/png/first.png"
        width: source.width 
        height: source.height
        asynchronous: true
    }
    Image {
        x: 29; y: 88
        source: "qrc:/png/endstation.png"
        width: source.width 
        height: source.height
        asynchronous: true
    }
    Item {
        x:95; y: 88
        width: 114; height: 36
        Item {
            width: 114; height: 18
            Text {
                id: endstataiontext
                anchors.centerIn: parent
                text: Uidefine.textstation[endstation]
                font.pixelSize: 18
                font.family: "微软雅黑"
                font.weight: Font.Bold
            }
        }
        Item {
            y: 24
            width: 114; height: 10
            Text {
                id: endstataiontextenglish
                anchors.centerIn: parent
                text: Uidefine.textstationenglish[endstation]
                font.pixelSize: 10
                font.family: "微软雅黑"
                font.weight: Font.Bold
            }
        }
    }
    Image {
        x: 25; y: 130
        source: "qrc:/png/first.png"
        width: source.width 
        height: source.height
        asynchronous: true
    }
    Image {
        x: 68; y: 139
        source: "qrc:/png/nextstation.png"
        width: source.width 
        height: source.height
        asynchronous: true
    }
    Image {
        x: 25; y: 190
        source: "qrc:/png/first.png"
        width: source.width 
        height: source.height
        asynchronous: true
    }
    Item {
        x: 42; y: 200
        width: 148; height: 44
        Item {
            width: 148; height: 24
            Text {
                id: thisstationtext
                anchors.centerIn: parent
                text: Uidefine.textstation[nextstation]
                font.pixelSize: 24
                font.family: "微软雅黑"
                font.weight: Font.Bold
            }
        }
        Item {
            y: 29
            width: 148; height: 12
            Text {
                id: thisstationtextenglish
                anchors.centerIn: parent
                text: Uidefine.textstationenglish[nextstation]
                font.pixelSize: 12
                font.family: "微软雅黑"
                font.weight: Font.Bold
            }
        }
    }
    Train {
        x: 400; y: 107
        just: root.just
    }
    StationAnimation {
        x: 273; y: 38
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    StationName {
        x: 0; y: 0
    }
}
