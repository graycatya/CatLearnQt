import QtQuick 2.12
import QtQuick.Layouts 1.12
import GrayCatQtQuick 1.0
import QtGraphicalEffects 1.12
import "../"


Rectangle {
    id: democatsidecolumn
    color: "transparent"

    Rectangle {
        id: sideitemrectangle
        anchors.fill: parent
        anchors.margins: 30
        color: "#3C3C3C"

        ListModel {
            id: functionstates

            ListElement {
                itemimgsource: "Function_0.png"
                itemtext: qsTr("Function_0")
            }
            ListElement {
                itemimgsource: "Function_1.png"
                itemtext: qsTr("Function_1")
            }
            ListElement {
                itemimgsource: "Function_2.png"
                itemtext: qsTr("Function_2")
            }
            ListElement {
                itemimgsource: "Function_3.png"
                itemtext: qsTr("Function_3")
            }
        }

        CatSideColumn {
            id: catsidecolumn
            anchors.top: sideitemrectangle.top
            anchors.bottom: sideitemrectangle.bottom
            listviewitem.model: functionstates
            showhighlight: true
            sideslip: true



            //anchors.centerIn: sideitemrectangle

            color: "#2C2C2C"

            listviewitem.delegate: Rectangle {
                height: catsidecolumn.minWidth
                width: catsidecolumn.width
                color: "transparent"
                MouseArea {
                    id: transarea
                    visible: true

                    anchors.fill: parent
                    // 悬停事件是否被处理
                    hoverEnabled: true
                    /* 此属性保存组合的鼠标事件
                     * 是否会自动传播到与此鼠标区域重叠但视觉堆叠顺序较低的其他鼠标区域
                    */
                    //propagateComposedEvents: true
                    // 此属性保存此鼠标区域的光标形状
                    cursorShape: enabled ? Qt.PointingHandCursor : Qt.ForbiddenCursor

                    //将accept设置为true将防止鼠标事件传播到此项下面的项。
                    onDoubleClicked: { mouse.accepted = false; }
                    onPositionChanged: {
                        mouse.accepted = false;
                    }
                    /*onPressed: {
                        mouse.accepted = false;
                    }
                    onPressAndHold: {
                        mouse.accepted = false;
                    }*/
                    onClicked: {
                        catsidecolumn.listviewitem.currentIndex = index
                        catsidecolumn.currentindex(index)
                        if(!catsidecolumn.showhighlight)
                        {
                            color = "#3C3C3C"
                        }
                        mouse.accepted = false;
                    }
                    onReleased: {
                        mouse.accepted = false;
                    }

                    onEntered: {
                        //console.log("index: " + catsidecolumn.listviewitem.currentIndex)
                        if(catsidecolumn.listviewitem.currentIndex !== index && !catsidecolumn.showhighlight)
                        {
                            color = "#4C4C4C"
                        }
                    }

                    onExited: {
                        if(catsidecolumn.listviewitem.currentIndex !== index && !catsidecolumn.showhighlight)
                        {
                            color = "transparent"
                        }
                    }
                }



                    RowLayout {
                        anchors.fill: parent
                        spacing: 10
                        Item {
                            Layout.preferredWidth: catsidecolumn.minWidth
                            Layout.preferredHeight: catsidecolumn.minWidth
                            Image {
                                anchors.centerIn: parent
                                source: ProjectObject.getCurrentResourcePath() + itemimgsource
                                sourceSize.width: catsidecolumn.minWidth/2
                                sourceSize.height: catsidecolumn.minWidth/2
                            }
                        }

                        Text {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            font.family: catsidecolumn.fontfamily
                            font.pixelSize: catsidecolumn.fontpixsize
                            color: catsidecolumn.fontcolor
                            verticalAlignment: Text.AlignVCenter

                            text: itemtext

                            visible: catsidecolumn.state === "hideText" ? false : true

                        }
                        Item {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                        }
                    }




                Component.onCompleted: {
                    catsidecolumn.currentindex.connect(function(updateindex){
                        //console.log("updateindex: " + updateindex)
                        if(!catsidecolumn.showhighlight)
                        {
                            if(updateindex !== index)
                            {
                                color = "transparent"
                            } else {
                                color = "#3C3C3C"
                            }
                        }
                    });
                    if(index === 0 && !catsidecolumn.showhighlight)
                    {
                        color = "#3C3C3C"
                    }
                }
            }


            listviewitem.highlight: Rectangle {
                height: catsidecolumn.minWidth
                width: catsidecolumn.width
                color: "#3C3C3C"
                visible: catsidecolumn.showhighlight

            }

            listviewitem.highlightFollowsCurrentItem: catsidecolumn.showhighlight;
            listviewitem.focus: catsidecolumn.showhighlight;

            width: 60
        }
    }

    DropShadow {
        anchors.fill: sideitemrectangle
        horizontalOffset: 0
        verticalOffset: 0
        radius: 10.0
        samples: 16
        color: "#3FFFFFFF"
        source: sideitemrectangle
    }

}
