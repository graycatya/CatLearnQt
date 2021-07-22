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
        signal addData();
        signal subtractData();
        signal clearData();
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
                webSocket.onTextMessageReceived.connect(function(data){
                    catLog.debug_print("DemoCatEchars: " + data);
                });
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

        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            spacing: 5

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

            RowLayout {
                Layout.preferredHeight: 30
                Layout.maximumHeight: 30
                Layout.fillWidth: true

                Rectangle {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    color: "transparent"
                }

                CatButtonImage {
                    id: addbutton
                    Layout.preferredWidth: 30
                    Layout.preferredHeight: 30

                    backImage.width: addbutton.width
                    backImage.height: addbutton.height
                    btnImgNormal: ProjectObject.getCurrentResourcePath() + "AddImage.png"
                    btnImgHovered: ProjectObject.getCurrentResourcePath() + "AddImage.png"
                    btnImgPressed: ProjectObject.getCurrentResourcePath() + "AddImage.png"
                    btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "AddImage.png"
                    backgroundColor: "#414141"
                    backgroundColor_hovered: "#414141"
                    backgroundColor_pressed: "#414141"
                    imagebackground.border.width: addbutton.pressed ? 3 : (addbutton.hovered ? 1 : 0)
                    imagebackground.border.color: "#1171AE"
                    imagebackground.radius: 5
                    onClicked: {
                        chartObject.addData();
                    }
                }

                CatButtonImage {
                    id: subtractbutton
                    Layout.preferredWidth: 30
                    Layout.preferredHeight: 30

                    backImage.width: subtractbutton.width
                    backImage.height: subtractbutton.height
                    btnImgNormal: ProjectObject.getCurrentResourcePath() + "SubtractImage.png"
                    btnImgHovered: ProjectObject.getCurrentResourcePath() + "SubtractImage.png"
                    btnImgPressed: ProjectObject.getCurrentResourcePath() + "SubtractImage.png"
                    btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "SubtractImage.png"
                    backgroundColor: "#414141"
                    backgroundColor_hovered: "#414141"
                    backgroundColor_pressed: "#414141"
                    imagebackground.border.width: subtractbutton.pressed ? 3 : (subtractbutton.hovered ? 1 : 0)
                    imagebackground.border.color: "#1171AE"
                    imagebackground.radius: 5
                    onClicked: {
                        chartObject.subtractData();
                    }
                }

                CatButtonImage {
                    id: clearbutton
                    Layout.preferredWidth: 30
                    Layout.preferredHeight: 30

                    backImage.width: clearbutton.width
                    backImage.height: clearbutton.height
                    btnImgNormal: ProjectObject.getCurrentResourcePath() + "ClearImage.png"
                    btnImgHovered: ProjectObject.getCurrentResourcePath() + "ClearImage.png"
                    btnImgPressed: ProjectObject.getCurrentResourcePath() + "ClearImage.png"
                    btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "ClearImage.png"
                    backgroundColor: "#414141"
                    backgroundColor_hovered: "#414141"
                    backgroundColor_pressed: "#414141"
                    imagebackground.border.width: clearbutton.pressed ? 3 : (clearbutton.hovered ? 1 : 0)
                    imagebackground.border.color: "#1171AE"
                    imagebackground.radius: 5
                    onClicked: {
                        chartObject.clearData();
                    }
                }

                Rectangle {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    color: "transparent"
                }
            }

        }

        WebChannel {
            id: channel
            registeredObjects: [chartObject]
        }

    }

}
