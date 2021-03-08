import QtQuick 2.12

import "qrc:/CustomControl"

Rectangle {
    id: root 
    color: "#a4a4a3"
    antialiasing: true
    width: 28; height: 28

    radius: width/2  //设置矩形圆角弧度
    border.color: "#912a2f" //设置边框的颜色
    border.width: 4   //设置边框的大小
    property int startstation: 0
    property int endstation: 0
    property int nextstation: 0
    property int stationid: 0
    property bool just: true
    property bool condition: just ? stationid < startstation || stationid > endstation : stationid > startstation || stationid < endstation
    state: stationid == nextstation ? "nextstation" : condition ? "overstation" : "notastation" 

    SequentialAnimation {
        id: animation 
        loops: Animation.Infinite
        running: false
        ColorAnimation {
            target: root 
            properties: "color"
            from: "#ff0000"
            to: "#01b812"
            duration: 1000
        }
        ColorAnimation {
            target: root 
            properties: "color"
            from: "#01b812"
            to: "#ff0000"
            duration: 1000
        }
    }

    states: [
        State {
            name: "overstation"
            PropertyChanges {
                target: root 
                color: "#a4a4a3"
            }
            PropertyChanges {
                target: animation  
                running: false
            }
        },
        State {
            name: "nextstation"
            PropertyChanges {
                target: animation  
                running: true
            }
        },
        State {
            name: "notastation"
            PropertyChanges {
                target: root 
                color: "#01b812"
            }
            PropertyChanges {
                target: animation  
                running: false
            }
        }
    ]
}
