import QtQuick 2.12 
import QtQuick.Window 2.12
import "qrc:/CustomControl"


Window {
    id: root
    width: 1366; height: 256
    visible: true

    property int startstation: 23
    property int endstation: 25
    property int nextstation: 24
    property bool just: true
    property bool doorOpen: true

    WelcomeUi {
        id: welcomeui
        visible: true
    }

    CurrentStationUi {
        id: currentstationui 
        visible: false
        endstation: root.endstation
        thisstation: root.startstation
        doorOpen: root.doorOpen
        just: root.just 
    }
    NextStationUi {
        id: nextstationui
        visible: false
        startstation: root.startstation
        endstation: root.endstation 
        nextstation: root.nextstation 
        just: root.just 
    }

    Fps {
        x: 1270; y: 0
        implicitHeight: 26
        implicitWidth: 26
        textSize: 26
    }

    Timer {
        id: timer
        interval: 14000
        repeat: true 
        running: true
        property bool berth: true
        onTriggered: {
            timer.interval = 6000
            welcomeui.visible = false
            if(root.startstation <= root.endstation && root.just == true)
            {
                root.just = true
                if(berth)
                {
                    if(root.startstation >= root.endstation)
                    { 
                        root.startstation = 25
                        root.endstation = 0
                        root.nextstation = 25
                        root.just = false
                    }
                    root.startstation = root.nextstation;
                    currentstationui.visible = true 
                    nextstationui.visible = false 
                    timer.berth = false
                } else {
                    currentstationui.visible = false 
                    nextstationui.visible = true
                    root.nextstation = root.startstation + 1;
                    root.doorOpen = !root.doorOpen;
                    timer.berth = true
                }
            } else if(root.startstation >= root.endstation && root.just == false)
            {
                root.just = false
                if(berth)
                {
                    if(root.startstation <= root.endstation)
                    {
                        root.startstation = 0
                        root.endstation = 25
                        root.nextstation = 0
                        root.just = true
                    }
                    root.startstation = root.nextstation;
                    currentstationui.visible = true 
                    nextstationui.visible = false 
                    timer.berth = false
                } else {
                    currentstationui.visible = false 
                    nextstationui.visible = true
                    root.nextstation = root.startstation - 1;
                    root.doorOpen = !root.doorOpen;
                    timer.berth = true
                }
            }
        }
    }
}
