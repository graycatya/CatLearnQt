import QtQuick 2.12

import "qrc:/CustomControl"

BarTypeProgressBar {
    id: pathway
    width: 92; height: 16
    clip: true
    property int stationid: 0
    property int startstation: 0
    property int endstation: 0
    property int nextstation: 0
    property bool just: true
    property int station: pathway.just ? pathway.stationid : pathway.stationid-1
    property bool condition: just ? pathway.nextstation > pathway.startstation : pathway.nextstation < pathway.startstation
    property bool pathwaycondition: pathway.just ? pathway.station < pathway.startstation + 1 || pathway.station > pathway.endstation : pathway.station > pathway.startstation - 1 || pathway.station < pathway.endstation
    state: pathway.nextstation == pathway.station && pathway.condition ? "nextstation" : pathway.pathwaycondition ? "overstation" : "notastation"
    states: [
        State {
            name: "overstation"
            PropertyChanges {
                target: pathway 
                backgroundColor: "#a4a4a3"
                progressbarColor: "transparent"
                running: false
            }
        },
        State {
            name: "nextstation"
            PropertyChanges {
                target: pathway
                backgroundColor: "#a4a4a3"
                progressbarColor: "#0cfc00"
                running: true
                duration: 2000
            }
        }, 
        State {
            name: "notastation"
            PropertyChanges {
                target: pathway 
                backgroundColor: "#0cfc00"
                progressbarColor: "transparent"
                running: false
            }
        }   
    ]
    onJustChanged: {
        pathway.running = false 
        pathway.running = true
    }
}
