import QtQuick 2.12

Item {
    id: root
    width: 1014; height: 186
    property int startstation: 1
    property int endstation: 20
    property int nextstation: 2
    property bool just: true
    ArcPathway {
        id: pathway0
        x: 13; y: 15
        progressbararcstartAngle: root.just ? -180 : -90
        to: root.just ? 90 : -90
        stationid: 1
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    Pathway {
        id: pathway1
        x: 50; y: 6
        rotation: root.just ? 0 : 180
        stationid: 2
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    Pathway {
        id: pathway2
        x: 142; y: 6
        rotation: root.just ? 0 : 180
        stationid: 3
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    Pathway {
        id: pathway3
        x: 243; y: 6
        rotation: root.just ? 0 : 180
        stationid: 4
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    Pathway {
        id: pathway4
        x: 324; y: 6
        rotation: root.just ? 0 : 180
        stationid: 5
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    Pathway {
        id: pathway5
        x: 414; y: 6
        rotation: root.just ? 0 : 180
        stationid: 6
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    Pathway {
        id: pathway6
        x: 515; y: 6
        rotation: root.just ? 0 : 180
        stationid: 7
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    Pathway {
        id: pathway7
        x: 597; y: 6
        rotation: root.just ? 0 : 180
        stationid: 8
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    Pathway {
        id: pathway8
        x: 697; y: 6
        rotation: root.just ? 0 : 180
        stationid: 9
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    Pathway {
        id: pathway9
        x: 779; y: 6
        rotation: root.just ? 0 : 180
        stationid: 10
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    Pathway {
        id: pathway10
        x: 869; y: 6
        rotation: root.just ? 0 : 180
        stationid: 11
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    ArcPathway {
        id: pathway11
        x: 955; y: 13
        rotation: 90
        progressbararcstartAngle: root.just ? -180 : -90
        to: root.just ? 90 : -90
        stationid: 12
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    Pathway {
        id: pathway12
        x: 954; y: 90
        rotation: root.just ? 90 : 270
        stationid: 13
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    ArcPathway {
        id: pathway13
        x: 956; y: 128
        rotation: 180
        progressbararcstartAngle: root.just ? -180 : -90
        to: root.just ? 90 : -90
        stationid: 14
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    Pathway {
        id: pathway14
        x: 870; y: 164
        rotation: root.just ? 180 : 0
        stationid: 15
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    Pathway {
        id: pathway15
        x: 777; y: 164
        rotation: root.just ? 180 : 0
        stationid: 16
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    Pathway {
        id: pathway16
        x: 680; y: 164
        rotation: root.just ? 180 : 0
        stationid: 17
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    Pathway {
        id: pathway17
        x: 597; y: 164
        rotation: root.just ? 180 : 0
        stationid: 18
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    Pathway {
        id: pathway18
        x: 506; y: 164
        rotation: root.just ? 180 : 0
        stationid: 19
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    Pathway {
        id: pathway19
        x: 415; y: 164
        rotation: root.just ? 180 : 0
        stationid: 20
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    Pathway {
        id: pathway20
        x: 324; y: 164
        rotation: root.just ? 180 : 0
        stationid: 21
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    Pathway {
        id: pathway21
        x: 233; y: 164
        rotation: root.just ? 180 : 0
        stationid: 22
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    Pathway {
        id: pathway22
        x: 142; y: 164
        rotation: root.just ? 180 : 0
        stationid: 23
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    Pathway {
        id: pathway23
        x: 50; y: 164
        rotation: root.just ? 180 : 0
        stationid: 24
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    ArcPathway {
        id: pathway24
        x: 12; y: 128
        rotation: 270
        progressbararcstartAngle: root.just ? -180 : -90
        to: root.just ? 90 : -90
        stationid: 25
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
        just: root.just
    }
    Station {
        id: station0
        x: 0; y: 38
        stationid: 0
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station1
        x: 38; y: 0
        stationid: 1
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station2
        x: 129; y: 0
        stationid: 2
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station3
        x: 220; y: 0
        stationid: 3
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station4
        x: 311; y: 0
        stationid: 4
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station5
        x: 402; y: 0
        stationid: 5
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station6
        x: 493; y: 0
        stationid: 6
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station7
        x: 584; y: 0
        stationid: 7
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station8
        x: 675; y: 0
        stationid: 8
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station9
        x: 766; y: 0
        stationid: 9
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station10
        x: 857; y: 0
        stationid: 10
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station11
        x: 948; y: 0
        stationid: 11
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station12
        x: 986; y: 38
        stationid: 12
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station13
        x: 986; y: 120
        stationid: 13
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station14
        x: 948; y: 158
        stationid: 14
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station15
        x: 857; y: 158
        stationid: 15
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station16
        x: 766; y: 158
        stationid: 16
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station17
        x: 675; y: 158
        stationid: 17
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station18
        x: 584; y: 158
        stationid: 18
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station19
        x: 493; y: 158
        stationid: 19
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station20
        x: 402; y: 158
        stationid: 20
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station21
        x: 311; y: 158
        stationid: 21
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station22
        x: 220; y: 158
        stationid: 22
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station23
        x: 129; y: 158
        stationid: 23
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station24
        x: 38; y: 158
        stationid: 24
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
    Station {
        id: station25
        x: 0; y: 120
        stationid: 25
        just: root.just
        startstation: root.startstation
        endstation: root.endstation
        nextstation: root.nextstation
    }
}
