import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12
import GrayCatQtQuick 1.0
import QtWebEngine 1.10
import QtWebView 1.1
import QtWebChannel 1.0
import QtWebSockets 1.1
import io.decovar.CatEchatswebChannel 1.0
import "../"

Rectangle {
    //id: demoimageflipable
    color: "transparent"

    QtObject {
        id: chartObject

        // ID, under which this object will be known at WebEngineView side
        WebChannel.id: "catecharts"

        //property string someProperty: "Break on through to the other side"

        signal updateForm(string form);

        /*function changeText(newText) {
            console.log(newText);
            txt.text = newText;
            return "New text length: " + newText.length;
        }*/
    }

    CatEchatswebChannel {
        id: catechatswebchannel
    }

    //WebSocket
    WebSocketServer {
        id: websocketserver
        listen: true
        port: 14618

        onClientConnected: {
            if(webSocket.status === WebSocket.Open)
            {
                channel.connectTo(catechatswebchannel)
                webSocket.onTextMessageReceived.connect(catechatswebchannel.textMessageReceive)
                catechatswebchannel.onMessageChanged.connect(webSocket.sendTextMessage);
            }
        }

        onErrorStringChanged: {
            console.log(qsTr("Server error: %1").arg(errorString));
        }
    }

    ListModel {
        id: chartModels
        ListElement {
            imagerec: "LineChart.png"
            chartform: "line"
        }
        ListElement {
            imagerec: "BarChart.png"
            chartform: "bar"
        }
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10

        spacing: 10

        ListView {
            id: chartfunctions
            Layout.fillHeight: true
            Layout.preferredWidth: 30
            Layout.minimumWidth: 30
            Layout.maximumWidth: 30
            spacing: 5
            clip: true
            focus: true


            model: chartModels

            delegate: Rectangle {
                width: 30
                height: 30

                color: "#414141"

                border.width: ListView.isCurrentItem ? 1 : 0
                radius: 5
                border.color: "#1171AE"

                Image {
                    anchors.fill: parent
                    source: ProjectObject.getCurrentResourcePath() + imagerec
                    width: 30
                    height: 30
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        chartfunctions.currentIndex = index  //实现item切换
                        chartObject.updateForm(chartform)
                    }
                }
            }
        }

        WebEngineView {
            id: webengine
            Layout.fillHeight: true
            Layout.fillWidth: true
            backgroundColor: "transparent"
            url: catconfig.getWebResourcePath() + "/charts.html";
            onGeometryChangeRequested: function(geometry) {
                webengine.x = geometry.x
                webengine.y = geometry.y
                webengine.width = geometry.width
                webengine.height = geometry.height
            }
        }

        WebChannel {
            id: channel
            registeredObjects: [chartObject]
        }

    }

}
