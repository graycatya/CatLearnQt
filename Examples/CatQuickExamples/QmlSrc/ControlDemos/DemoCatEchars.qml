import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12
import GrayCatQtQuick 1.0
import QtWebEngine 1.10
import QtWebChannel 1.0
import QtWebSockets 1.1
import "../"

Rectangle {
    //id: demoimageflipable
    color: "transparent"

    //WebSocket
    WebSocketServer {
        id: websocketserver
        listen: true
        port: 14618

        onClientConnected: {
            if(webSocket.status === webSocket.Open)
            {

            }
        }

        onErrorStringChanged: {

        }
    }

    WebEngineView {
        id: webengine
        anchors.fill: parent
        anchors.margins: 10
        backgroundColor: "transparent"
        url: catconfig.getWebResourcePath() + "/charts.html";
        onGeometryChangeRequested: function(geometry) {
            webengine.x = geometry.x
            webengine.y = geometry.y
            webengine.width = geometry.width
            webengine.height = geometry.height
        }
    }

}
