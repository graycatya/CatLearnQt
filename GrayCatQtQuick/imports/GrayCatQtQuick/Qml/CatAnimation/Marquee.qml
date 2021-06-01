import QtQuick 2.12


Rectangle {
    id: root
    //width: 200; height: 100
    color: "steelblue"
    clip: true
    anchors.centerIn: parent

    //Text元素抛出
    property alias text: marquee.text
    property alias font: marquee.font
    property alias text_color: marquee.color

    //SequentialAnimation元素抛出
    property alias animation_loops: marquee_sequential.loops 
    property alias animation_running: marquee_sequential.running

    //PropertyAnimation元素抛出
    property alias animation_duration: marquee_property.duration


    Text {
        id: marquee
        verticalAlignment: Text.AlignVCenter
        SequentialAnimation {
            id: marquee_sequential
            loops: Animation.Infinite
            PropertyAnimation {
                id: marquee_property
                target: marquee
                //property: "x"
                //from: root.width
                //to: - marquee.width
                //duration: 1000
            }
        }
    }

    states: [
        State {
            name: "lefttoright"
            PropertyChanges {
                target: marquee_property
                property: "x"
                from: root.width
                to: - marquee.width
            }
        },
        State {
            name: "righttoleft"
            PropertyChanges {
                target: marquee_property
                property: "x"
                from: - marquee.width
                to: root.width
            }
        },
        State {
            name: "uptodown"
            PropertyChanges {
                target: marquee_property
                property: "y"
                from: -marquee.height
                to: root.height 
            }
        },
        State {
            name: "downtoup"
            PropertyChanges {
                target: marquee_property
                property: "y"
                from: root.height
                to: -marquee.height
            }
        } 
    ]

}