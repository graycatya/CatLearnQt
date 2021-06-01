import QtQuick 2.12


Rectangle{
    id: root
    width: 180; height: 30
    implicitWidth: 180
    implicitHeight: 30
    clip: true
    anchors.centerIn: parent
    color: "white"
    border.color: "gray"


    property string text: ipone.text + "." + iptwo.text + "." + ipthree.text + "." + ipfour.text
    property color textcolor: "black"
    property color corsorcolor: "red"

    QtObject {
        id: corsor 
        property bool corsorshow: true
        property bool corsorshowone: true 
        property bool corsorshowtwo: true 
        property bool corsorshowthree: true 
        property bool corsorshowfour: true
    }


    
    
    TextInput {
        id: ipone
        clip: true
        x: 1; y: 1
        width: (root.width -2) * (2/11); height: root.height - 2
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        KeyNavigation.tab: iptwo
        selectByMouse: true
        color: textcolor
        focus: false
        cursorDelegate: cursorone
        
        text: "0"
        font.pointSize: root.height * 0.4

        validator: RegExpValidator{regExp:/(2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2}/}

        onTextEdited: {
            focusswitch(ipone, iptwo)
        }
        onFocusChanged: {
            if(ipone.focus == true)
            {
                //console.log("ipone true");
                corsor.corsorshowone = true 
                corsor.corsorshowtwo = false 
                corsor.corsorshowthree = false
                corsor.corsorshowfour = false 
            } else {
                //console.log("ipone false");
            }
        }
    }

    Rectangle {
        id: dotone
        y: 1
        width: (root.width -2) * (1/11); height: root.height - 2
        anchors.left: ipone.right
        Text {
            width: parent.width; height: parent.height
            color: textcolor
            text: "."
            font.pointSize: root.height * 0.4

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    TextInput {
        id: iptwo
        clip: true
        y: 1
        width: (root.width -2) * (2/11); height: root.height - 2
        anchors.left: dotone.right
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        KeyNavigation.tab: ipthree
        selectByMouse: true
        color: textcolor
        focus: false
        cursorDelegate: cursortwo

        text: "0"
        font.pointSize: root.height * 0.4

        validator: RegExpValidator{regExp:/(2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2}/}

        onTextEdited: {
            focusswitch(iptwo, ipthree)
            if(iptwo.text == "")
            {
                ipone.focus = true
            }
        }
        onFocusChanged: {
            if(iptwo.focus == true)
            {
                //console.log("iptwo true");
                corsor.corsorshowone = false 
                corsor.corsorshowtwo = true
                corsor.corsorshowthree = false
                corsor.corsorshowfour = false 
            } else {
                //console.log("iptwo false");
            }
        }
    }

    Rectangle {
        id: dottwo
        y: 1
        width: (root.width -2) * (1/11); height: root.height - 2
        anchors.left: iptwo.right
        Text {
            width: parent.width; height: parent.height
            color: textcolor
            text: "."
            font.pointSize: root.height * 0.4

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    TextInput {
        id: ipthree
        clip: true
        y: 1
        width: (root.width -2) * (2/11); height: root.height - 2
        anchors.left: dottwo.right
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        KeyNavigation.tab: ipfour
        selectByMouse: true
        color: textcolor
        focus: false
        cursorDelegate: cursorthree

        text: "0"
        font.pointSize: root.height * 0.4

        validator: RegExpValidator{regExp:/(2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2}/}

        onTextEdited: {
            focusswitch(ipthree, ipfour)
            if(ipthree.text == "")
            {
                iptwo.focus = true
            }
        }
        onFocusChanged: {
            if(ipthree.focus == true)
            {
                //console.log("ipthree true");
                corsor.corsorshowone = false 
                corsor.corsorshowtwo = false 
                corsor.corsorshowthree = true
                corsor.corsorshowfour = false 
            } else {
                //console.log("ipthree false");
            }
        }
    }

    Rectangle {
        id: dotthree
        y: 1
        width: (root.width -2) * (1/11); height: root.height - 2
        anchors.left: ipthree.right
        Text {
            width: parent.width; height: parent.height
            color: textcolor
            text: "."
            font.pointSize: root.height * 0.4

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    TextInput {
        id: ipfour
        clip: true
        y: 1
        width: (root.width -2) * (2/11); height: root.height - 2
        anchors.left: dotthree.right
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        KeyNavigation.tab: ipone
        selectByMouse: true
        color: textcolor
        focus: false
        cursorDelegate: cursorfour

        text: "0"
        font.pointSize: root.height * 0.4

        validator: RegExpValidator{regExp:/(2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2}/}

        onTextEdited: {
            //focusswitch(ipone, iptwo)
            if(ipfour.text == "")
            {
                ipthree.focus = true
            }
        }
        onFocusChanged: {
            if(ipfour.focus == true)
            {
                //console.log("ipfour true");
                corsor.corsorshowone = false 
                corsor.corsorshowtwo = false 
                corsor.corsorshowthree = false 
                corsor.corsorshowfour = true 
            } else {
                //console.log("ipfour false");
            }
        }
    }

    Component {
        id: cursorone
        Rectangle {
            width: 1
            visible: corsor.corsorshow
            height: root.height * 0.7
            color: corsor.corsorshowone ? root.corsorcolor : "transparent"
        }
    }
    Component {
        id: cursortwo
        Rectangle {
            width: 1
            visible: corsor.corsorshow
            height: root.height * 0.7
            color: corsor.corsorshowtwo ? root.corsorcolor : "transparent"
        }
    }
    Component {
        id: cursorthree
        Rectangle {
            width: 1
            visible: corsor.corsorshow
            height: root.height * 0.7
            color: corsor.corsorshowthree ? root.corsorcolor : "transparent"
        }
    }
    Component {
        id: cursorfour
        Rectangle {
            width: 1
            visible: corsor.corsorshow
            height: root.height * 0.7
            color: corsor.corsorshowfour ? root.corsorcolor : "transparent"
        }
    }

    Timer {
        interval: 500;
        repeat: true;
        running: true;
        onTriggered: {
            corsor.corsorshow = !corsor.corsorshow
        }
    }

    function focusswitch(inputone, inputtwo)
    {

        if (inputone.length === 3)
        {
            inputtwo.focus = true
        } else if(inputone.text > 25 && inputone.length === 2)
        {
            inputtwo.focus = true
        }
    }

}
