import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QCatGrayQuick

import "../"


Rectangle {
    id: democatsidecolumn
    color: "transparent"

    property color democatsidecolumnbackcolor: ProjectObject.democatsidecolumnback_color
    property color sideitemrectanglebackcolor: ProjectObject.sideitemrectangleback_color
    property color catsidecolumnitem_SelectColor: ProjectObject.catsidecolumnitem_SelectColor
    property color catsidecolumnitem_HoverColor: ProjectObject.catsidecolumnitem_HoverColor
    property color catsidecolumnitem_DefaultColor: ProjectObject.catsidecolumnitem_DefaultColor
    property color switchbuttonback_DefaultColor: ProjectObject.switchbuttonback_DefaultColor
    property color switchbuttonback_CheckColor: ProjectObject.switchbuttonback_CheckColor
    property color switchbuttonCircle_Color: ProjectObject.switchbuttonCircle_Color

    Rectangle {
        id: sideitemrectangle
        anchors.fill: parent
        anchors.margins: 30
        color: democatsidecolumnbackcolor

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
            showhighlight: false
            sideslip: true
            fontcolor: ProjectObject.catsidecolumnitem_FunctionColor

            //anchors.centerIn: sideitemrectangle

            color: sideitemrectanglebackcolor

            listviewitem.delegate: Rectangle {
                height: catsidecolumn.minWidth
                width: catsidecolumn.width
                color: "transparent"

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

                    MouseArea {
                        id: transarea
                        //visible: true

                        anchors.fill: parent
                        // 悬停事件是否被处理
                        //hoverEnabled: true
                        /* 此属性保存组合的鼠标事件
                         * 是否会自动传播到与此鼠标区域重叠但视觉堆叠顺序较低的其他鼠标区域
                        */
                        propagateComposedEvents: true
                        // 此属性保存此鼠标区域的光标形状
                        cursorShape: enabled ? Qt.PointingHandCursor : Qt.ForbiddenCursor

                        //将accept设置为true将防止鼠标事件传播到此项下面的项。
                        onDoubleClicked: function(mouse) { mouse.accepted = false; }
                        onPositionChanged: function(mouse) {
                            mouse.accepted = false;
                        }
                        /*onPressed: {
                            mouse.accepted = false;
                        }
                        onPressAndHold: {
                            mouse.accepted = false;
                        }*/
                        onClicked: function(mouse) {
                            mouse.accepted = false;
                        }
                        onReleased: function(mouse) {
                            mouse.accepted = false;
                        }
                    }




                Component.onCompleted: {
                    ProjectObject.updateCurrentThemeed.connect(function(){
                        if (typeof(catsidecolumn) !== 'undefined')
                        {
                            if(catsidecolumn.listviewitem.currentIndex === index)
                            {
                                if(!catsidecolumn.showhighlight)
                                {
                                    color = catsidecolumnitem_SelectColor
                                }
                            }
                        }
                    });
                    catsidecolumn.mouseClicked.connect(function(updateindex){
                        if(index === updateindex)
                        {
                            if(!catsidecolumn.showhighlight)
                            {
                                color = catsidecolumnitem_SelectColor
                            }
                        } else {
                           color = catsidecolumnitem_DefaultColor
                        }
                    })
                    catsidecolumn.mouseMovesindex.connect(function(updateindex){
                        if(index === updateindex)
                        {
                            if(catsidecolumn.listviewitem.currentIndex !== index && !catsidecolumn.showhighlight)
                            {
                                color = catsidecolumnitem_HoverColor
                            }
                        } else {
                            if(catsidecolumn.listviewitem.currentIndex !== index && !catsidecolumn.showhighlight)
                            {
                                color = catsidecolumnitem_DefaultColor
                            }
                        }
                    })
                    catsidecolumn.mouseExited.connect(function(){
                        if(catsidecolumn.listviewitem.currentIndex !== index && !catsidecolumn.showhighlight)
                        {
                            color = catsidecolumnitem_DefaultColor
                        }
                    })
//                    catsidecolumn.currentindex.connect(function(updateindex){
//                        //console.log("updateindex: " + updateindex)
//                        if(!catsidecolumn.showhighlight)
//                        {
//                            if(updateindex !== index)
//                            {
//                                color = catsidecolumnitem_DefaultColor
//                            } else {
//                                color = catsidecolumnitem_SelectColor
//                            }
//                        } else {
//                            color = catsidecolumnitem_DefaultColor
//                        }
//                    });
                    if(index === 0 && !catsidecolumn.showhighlight)
                    {
                        color = catsidecolumnitem_SelectColor
                    }
                }
            }


            listviewitem.highlight: Rectangle {
                height: catsidecolumn.minWidth
                width: catsidecolumn.width
                color: catsidecolumn.showhighlight ? catsidecolumnitem_SelectColor : "transparent"
                visible: catsidecolumn.showhighlight

            }

            listviewitem.highlightFollowsCurrentItem: true
            listviewitem.focus: true

            width: 60
        }

        Item {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: catsidecolumn.right
            Repeater {
                id: switchRepeater
                model: [""]


                Switch {
                    id: switchshowhighlight
                    anchors.centerIn: parent
                    width: 60
                    height: 36

                    indicator: Rectangle {
                        width: 60
                        height: 36
                        radius: height / 2
                        color: switchshowhighlight.checked ? switchbuttonback_CheckColor : switchbuttonback_DefaultColor
                        border.width: 2
                        border.color: switchbuttonback_CheckColor

                        Rectangle {
                            id: switchtransitioncircle
                            x: 1
                            width: switchshowhighlight.checked ? parent.height - 4 : parent.height - 2
                            height: width
                            radius: width / 2
                            anchors.verticalCenter: parent.verticalCenter
                            color: switchbuttonCircle_Color
                            //border.color: "#C4C4C4"

                            NumberAnimation on x {
                                id: switchtransitioncircleAnimation
                                duration: 200
                            }
                            function animationTo()
                            {
                                switchtransitioncircle.width = switchshowhighlight.checked ? parent.height - 4 : parent.height - 2
                                switchtransitioncircleAnimation.from = x
                                switchtransitioncircleAnimation.to = switchshowhighlight.checked ? parent.width - switchtransitioncircle.width - 1 : 1
                                switchtransitioncircleAnimation.running = true
                            }
                        }
                    }

                    onVisualPositionChanged: {
                        catsidecolumn.showhighlight = visualPosition
                        //catsidecolumn.currentindex(catsidecolumn.listviewitem.currentIndex)
                        switchtransitioncircle.animationTo()
                    }
                }
            }
        }
    }

    CatDropShadow {
        anchors.fill: sideitemrectangle
        horizontalOffset: 0
        verticalOffset: 0
        radius: 10.0
        samples: 16
        color: "#3FFFFFFF"
        source: sideitemrectangle
    }

}
