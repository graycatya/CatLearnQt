import QtQuick 2.12

Item {
    id: root 
    property var textVar: ["h", "e", "l", "l", "o", " w", "o", "r", "l", "d", "!"]
    property var textIndex: 0
    property font textfont
    property var color: "blue"
    property int interval: 500
    height: textshow.font.pixelSize

    Text {
        id: textshow 
        height: parent.height 
        color: root.color
        font: textfont
        verticalAlignment: Text.AlignVCenter
        text: ""
    }
    Timer {
        id: textTimer 
        interval: root.interval
        running: true 
        repeat: true 
        onTriggered: {
            if (textIndex == textVar.length)
            {
                textshow.text = ""
                textIndex = 0;
                return;
            }
            textshow.text = textshow.text + textVar[textIndex]
            textIndex++;
        }
    }
    onVisibleChanged: {
        if (root.visible == true)
        {
            textTimer.running = true
        } else
        {
            textTimer.running = false
        }
    }
}
