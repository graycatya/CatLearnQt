import QtQuick 2.12 

import "qrc:/CustomControl"
import "UiConfig.js" as Uidefine


Item {
    id: root
    width: 1366 
    height: 256 
    property int endstation: 0
    property int thisstation: 0
    property bool just: true
    property bool doorOpen: false
    
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
                font.family: "Ubuntu"
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
                font.family: "Ubuntu"
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
        source: "qrc:/png/thisstation.png"
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
                text: Uidefine.textstation[thisstation]
                font.pixelSize: 24
                font.family: "Ubuntu"
                font.weight: Font.Bold
            }
        }
        Item {
            y: 29
            width: 148; height: 12
            Text {
                id: thisstationtextenglish
                anchors.centerIn: parent
                text: Uidefine.textstationenglish[thisstation]
                font.pixelSize: 12
                font.family: "Ubuntu"
                font.weight: Font.Bold
            }
        }
    }


    //动画
    Item {
        id: leftround
        x: 241; y: 61
        width: 198; height: 179
        Item {
            width: 198; height: 107
            Image {
                //x: 287; y: 61
                anchors.centerIn: parent
                source: "qrc:/png/roundblack.png"
                asynchronous: true
            }
        }
        Item {
            y: 127
            width: 198; height: 24
            Text {
                id: animationone
                anchors.centerIn: parent
                text: Uidefine.textstation[thisstation-1]
                font.pixelSize: 24
                font.family: "Ubuntu"
                font.weight: Font.Bold
            }
        }
        Item {
            y: 161
            width: 198; height: 16
            Text {
                id: animationoneenglish
                anchors.centerIn: parent
                text: Uidefine.textstationenglish[thisstation-1]
                font.pixelSize: 16
                font.family: "Ubuntu"
                font.weight: Font.Bold
            }
        }
    }
    Image {
        id: leftarrowright
        x: 434; y: 84
        source: "qrc:/png/arrowright.png"
        rotation: root.just ? 0 : 180
        asynchronous: true
    }

    Item {
        id: centreround
        x: 550; y: 40
        width: 198; height: 200
        Item {
            width: 198; height: 138
            ImageScale {
                //x: 580; y: 40
                width: 138; height: 138
                anchors.centerIn: parent
                source: "qrc:/png/roundblue.png"
                animation_running: true
                animation_duration: 2000
            }
        }
        Item {
            y: 146
            width: 198; height: 24
            Text {
                id: animationtwo
                anchors.centerIn: parent
                text: Uidefine.textstation[thisstation]
                font.pixelSize: 24
                font.family: "Ubuntu"
                font.weight: Font.Bold
            }
        }
        Item {
            y: 180
            width: 198; height: 16
            Text {
                id: animationtwoenglish
                anchors.centerIn: parent
                text: Uidefine.textstationenglish[thisstation]
                font.pixelSize: 16
                font.family: "Ubuntu"
                font.weight: Font.Bold
            }
        }
    }
    Image {
        id: rightarrowright
        x: 758; y: 85
        source: "qrc:/png/arrowright.png"
        rotation: root.just ? 0 : 180
        asynchronous: true
    }

    Item {
        id: rightround
        x: 859; y: 61
        width: 198; height: 179
        Item {
            width: 198; height: 107
            Image {
                anchors.centerIn: parent
                source: "qrc:/png/roundgreen.png"
                asynchronous: true
            }
        }
        Item {
            y: 127
            width: 198; height: 24
            Text {
                id: animationthree
                anchors.centerIn: parent
                text: Uidefine.textstation[thisstation+1]
                font.pixelSize: 24
                font.family: "Ubuntu"
                font.weight: Font.Bold
            }
        }
        Item {
            y: 161
            width: 198; height: 16
            Text {
                id: animationthreeenglish
                anchors.centerIn: parent
                text: Uidefine.textstationenglish[thisstation+1]
                font.pixelSize: 16
                font.family: "Ubuntu"
                font.weight: Font.Bold
            }
        }
    }

    DoorOpen { x: 1126; y: 70; visible: doorOpen  }

    DoorOtherOpened { x: 1143; y: 70; visible: !doorOpen }


    Image {
        x: 1117; y: 173
        visible: doorOpen
        source: "qrc:/png/doorsonthis.png"
        asynchronous: true
    }

    Image {
        x: 1099; y: 174
        visible: !doorOpen
        source: "qrc:/png/doorsonopened.png"
        asynchronous: true
    }
    onThisstationChanged: {
        if(root.just)
        {
            if(root.thisstation == 0)
            {
                leftround.visible = false;
                leftarrowright.visible = false;

                centreround.x = 550 - 200; 
                centreround.y = 40;
                centreround.visible = true;

                rightarrowright.x = 758 - 200; 
                rightarrowright.y = 85;
                rightarrowright.visible = true;

                rightround.x = 859 - 200; 
                rightround.y = 61;
                rightround.visible = true;

            } else if (root.thisstation == 25)
            {
                leftround.x = 241 + 200; 
                leftround.y = 61;
                leftround.visible = true;

                leftarrowright.x = 434 + 200; 
                leftarrowright.y = 84;
                leftarrowright.visible = true;

                centreround.x = 550 + 200; 
                centreround.y = 40;
                centreround.visible = true;

                rightarrowright.visible = false;
                rightround.visible = false;
            } else {
                leftround.x = 241; 
                leftround.y = 61;
                leftround.visible = true;

                leftarrowright.x = 434; 
                leftarrowright.y = 84;
                leftarrowright.visible = true;

                centreround.x = 550; 
                centreround.y = 40;
                centreround.visible = true;

                rightarrowright.x = 758; 
                rightarrowright.y = 85;
                rightarrowright.visible = true;

                rightround.x = 859; 
                rightround.y = 61;
                rightround.visible = true;
            }
        } else {
            if(root.thisstation == 0)
            {
                leftround.visible = false;
                leftarrowright.visible = false;

                centreround.x = 550 - 200; 
                centreround.y = 40;
                centreround.visible = true;

                rightarrowright.x = 758 - 200; 
                rightarrowright.y = 85;
                rightarrowright.visible = true;

                rightround.x = 859 - 200; 
                rightround.y = 61;
                rightround.visible = true;

            } else if (root.thisstation == 25)
            {
                leftround.x = 859 + 200; 
                leftround.y = 61;
                leftround.visible = true;

                leftarrowright.x = 434 + 200; 
                leftarrowright.y = 84;
                leftarrowright.visible = true;

                centreround.x = 550 + 200; 
                centreround.y = 40;
                centreround.visible = true;
                rightarrowright.visible = false;
                rightround.visible = false;
            } else {
                leftround.x = 859; 
                leftround.y = 61;
                leftround.visible = true;

                leftarrowright.x = 434; 
                leftarrowright.y = 84;
                leftarrowright.visible = true;

                centreround.x = 550; 
                centreround.y = 40;
                centreround.visible = true;

                rightarrowright.x = 758; 
                rightarrowright.y = 85;
                rightarrowright.visible = true;

                rightround.x = 241;
                rightround.y = 61;
                rightround.visible = true;
            }
        }
    }
}
