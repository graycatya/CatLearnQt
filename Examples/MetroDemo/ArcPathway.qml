import QtQuick 2.12

import "qrc:/CustomControl"

ArcProgressBar {
    id: arcpathway
    width: 46; height: 46
    strokeWidth: 16
    //clip: true
    property int stationid: 0
    property int startstation: 0
    property int endstation: 0
    property int nextstation: 0
    property bool just: true
    property int station: arcpathway.just ? arcpathway.stationid : arcpathway.stationid-1
    property bool condition: just ? arcpathway.nextstation > arcpathway.startstation : arcpathway.nextstation < arcpathway.startstation
    property bool pathwaycondition: arcpathway.just ? arcpathway.station < arcpathway.startstation + 1 || arcpathway.station > arcpathway.endstation : arcpathway.station > arcpathway.startstation - 1 || arcpathway.station < arcpathway.endstation
    state: arcpathway.nextstation == arcpathway.station && arcpathway.condition ? "nextstation" : arcpathway.pathwaycondition ? "overstation" : "notastation"

    states: [
        State {
            name: "overstation"
            PropertyChanges {
                target: arcpathway
                backdropstrokeColor: "#a4a4a3"
                progressbarstrokeColor: "transparent"
                running: false
            }
        },
        State {
            name: "nextstation"
            PropertyChanges {
                target: arcpathway
                
                backdropstrokeColor: "#a4a4a3"
                progressbarstrokeColor: "#0cfc00"
                duration: 1000
                running: true
            }
        }, 
        State {
            name: "notastation"
            PropertyChanges {
                target: arcpathway 
                backdropstrokeColor: "#0cfc00"
                progressbarstrokeColor: "transparent"
                running: false
            }
        } 
    ]
    onJustChanged: {
        arcpathway.running = false 
        arcpathway.running = true
    }
    onVisibleChanged: {
        if (arcpathway.visible == true)
        {
            arcpathway.running = true
        } else
        {
            arcpathway.running = false
        }
    }
}
