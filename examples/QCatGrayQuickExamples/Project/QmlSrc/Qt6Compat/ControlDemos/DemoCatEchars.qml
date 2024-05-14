import QtQuick
import QtQuick.Layouts

import QCatGrayQuick
import QtWebEngine
import QtWebView
import QtWebChannel
import QtWebSockets
import io.decovar.CatEchatswebChannel
import "../"

Rectangle {
    id: root
    //id: demoimageflipable
    color: "transparent"

    QtObject {
        id: chartObject

        // ID, under which this object will be known at WebEngineView side
        WebChannel.id: "catecharts"

        //property string someProperty: "Break on through to the other side"

        signal updateForm(string form);
        signal updateStyle(string style);

        /*function changeText(newText) {
            console.log(newText);
            txt.text = newText;
            return "New text length: " + newText.length;
        }*/
        signal addData();
        signal subtractData();
        signal clearData();

        function getStyle()
        {
            return
        }

    }

    CatEchatswebChannel {
        id: catechatswebchannel
    }

    //WebSocket
    WebSocketServer {
        id: websocketserver
        listen: true
        port: 14618

        onClientConnected: function(webSocket) {
            if(webSocket.status === WebSocket.Open)
            {
                channel.connectTo(catechatswebchannel)
                webSocket.onTextMessageReceived.connect(catechatswebchannel.textMessageReceive)
                webSocket.onTextMessageReceived.connect(function(data){
                    console.log("DemoCatEchars: " + data);
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
        ListElement {
            imagerec: "ScatterChart.png"
            chartform: "scatter"
        }
        ListElement {
            imagerec: "KChart.png"
            chartform: "k"
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

                color: ProjectObject.defaultButton_DefaultColor

                border.width: ListView.isCurrentItem ? 1 : 0
                radius: 5
                border.color: ProjectObject.defaultButtonBorder_DefaultColor

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

                onLoadProgressChanged: {

                    if(loadProgress == 100)
                    {
                        timer.start();
                    }
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
                    backgroundColor: ProjectObject.defaultButton_DefaultColor
                    backgroundColor_hovered: ProjectObject.defaultButton_HoverColor
                    backgroundColor_pressed: ProjectObject.defaultButton_PressColor
                    imagebackground.border.width: addbutton.pressed ? 3 : (addbutton.hovered ? 1 : 0)
                    imagebackground.border.color: ProjectObject.defaultButtonBorder_DefaultColor
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
                    backgroundColor: ProjectObject.defaultButton_DefaultColor
                    backgroundColor_hovered: ProjectObject.defaultButton_HoverColor
                    backgroundColor_pressed: ProjectObject.defaultButton_PressColor
                    imagebackground.border.width: subtractbutton.pressed ? 3 : (subtractbutton.hovered ? 1 : 0)
                    imagebackground.border.color: ProjectObject.defaultButtonBorder_DefaultColor
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
                    backgroundColor: ProjectObject.defaultButton_DefaultColor
                    backgroundColor_hovered: ProjectObject.defaultButton_HoverColor
                    backgroundColor_pressed: ProjectObject.defaultButton_PressColor
                    imagebackground.border.width: clearbutton.pressed ? 3 : (clearbutton.hovered ? 1 : 0)
                    imagebackground.border.color: ProjectObject.defaultButtonBorder_DefaultColor
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

    Component.onCompleted: {
        ProjectObject.updateCurrentThemeed.connect(function(){
            if(typeof(visible) != "undefined" && visible)
            {
                chartObject.updateStyle(ProjectObject.themes.get(ProjectObject.currentTheme).name);
            }
        });
    }

    Timer {
        id: timer
        interval: 200
        onTriggered: {
            chartObject.updateStyle(ProjectObject.themes.get(ProjectObject.currentTheme).name);
        }
    }

}
