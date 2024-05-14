import QtQuick
import QtQuick.Layouts

import QCatGrayQuick
import TableViewModel
import QtQuick.Controls
import QtQml.Models
import "../"

Rectangle {
    id: demotableview
    color: "transparent"

    property int horHeaderHeight: 50
    //滚动条
    property color scrollBarColor: Qt.rgba(0, 0, 0, 0.4);
    property int scrollBarWidth: 6
    //列宽
    property variant columnWidthArr: [100,100,100,200]

    property var headerHor: [qsTr("Id"), qsTr("Button"), qsTr("Logo"), qsTr("String")]

    TableViewModel{

        id: tableviewmodel
        headerHor: ["Id", "Button", "Logo", "String"]

        initData: [
            {"Id": { "State" : "Id", "Value" : 1 },
                "Button": { "State" : "Button", "Value" : true  },
                "Logo": { "State" : "Logo", "Value" : "Raspi-PGB001.png" },
                "String": { "State" : "String", "Value" : "Text" }},
            {"Id": { "State" : "Id", "Value" : 2 },
                "Button": { "State" : "Button", "Value" : false  },
                "Logo": { "State" : "Logo", "Value" : "Raspi-PGB001.png" },
                "String": { "State" : "String", "Value" : "Text" }},
            {"Id": { "State" : "Id", "Value" : 3 },
                "Button": { "State" : "Button", "Value" : true  },
                "Logo": { "State" : "Logo", "Value" : "Raspi-PGB001.png" },
                "String": { "State" : "String", "Value" : "Text" }},
            {"Id": { "State" : "Id", "Value" : 4 },
                "Button": { "State" : "Button", "Value" : true  },
                "Logo": { "State" : "Logo", "Value" : "Raspi-PGB001.png" },
                "String": { "State" : "String", "Value" : "Text" }},
            {"Id": { "State" : "Id", "Value" : 5 },
                "Button": { "State" : "Button", "Value" : true  },
                "Logo": { "State" : "Logo", "Value" : "Raspi-PGB001.png" },
                "String": { "State" : "String", "Value" : "Text" }},
            {"Id": { "State" : "Id", "Value" : 6 },
                "Button": { "State" : "Button", "Value" : true  },
                "Logo": { "State" : "Logo", "Value" : "Raspi-PGB001.png" },
                "String": { "State" : "String", "Value" : "Text" }},
            {"Id": { "State" : "Id", "Value" : 7 },
                "Button": { "State" : "Button", "Value" : true  },
                "Logo": { "State" : "Logo", "Value" : "Raspi-PGB001.png" },
                "String": { "State" : "String", "Value" : "Text" }},
            {"Id": { "State" : "Id", "Value" : 8 },
                "Button": { "State" : "Button", "Value" : true  },
                "Logo": { "State" : "Logo", "Value" : "Raspi-PGB001.png" },
                "String": { "State" : "String", "Value" : "Text" }},
            {"Id": { "State" : "Id", "Value" : 9 },
                "Button": { "State" : "Button", "Value" : true  },
                "Logo": { "State" : "Logo", "Value" : "Raspi-PGB001.png" },
                "String": { "State" : "String", "Value" : "Text" }},
        ]

        onInitDataChanged: {

        }

    }

    Rectangle {
        id: tableback
        anchors.fill: parent
        anchors.topMargin: 20
        anchors.bottomMargin: 20
        anchors.rightMargin: 100
        anchors.leftMargin: 100
        color: ProjectObject.moreViewBackColor
        radius: 5



            TableView {
               id: table_view

               anchors{
                   right: parent.right
                   left: parent.left
                   bottom: parent.bottom
                   top: header_horizontal.bottom
                   bottomMargin: 20
               }

               clip: true
               boundsBehavior: Flickable.StopAtBounds
               columnSpacing: 0
               rowSpacing: 0

               rowHeightProvider: function (row) { return 50; }
               columnWidthProvider: function (column) {
                   return Math.max(1, (table_view.width - leftMargin) / table_view.columns)
               }

               onWidthChanged: {
                   columnWidthProvider = function (column) {
                       return Math.max(1, (table_view.width - leftMargin) / table_view.columns)
                   }
               }

               //视图的高度
               //contentHeight: rowHeightProvider(0) * rows + rowHeightProvider(rows-1)
               //视图的宽度
               //contentWidth:
               //content内容区域边距，但是不影响滚动条的位置
               //leftMargin:
               //topMargin:
               //此属性可以包含一个函数，该函数返回模型中每行的行高
               /*rowHeightProvider: function (row) {
                   return demotableview.verHeaderHeight;
               }*/
               //此属性可以保存一个函数，该函数返回模型中每个列的列宽
               /*columnWidthProvider: function (column) {
                   return demotableview.columnWidthArr[column];
                   //return Math.max(1, (table_view.width - leftMargin) / table_view.columns)
               }*/
               ScrollBar.vertical: ScrollBar {
                   id: scroll_vertical
                   anchors.right: parent.right
                   anchors.rightMargin: 0

                   //active: table_view.ScrollBar.vertical.active
                   //policy: ScrollBar.AsNeeded
                   contentItem: Rectangle{
                       visible: (scroll_vertical.size<1.0)
                       radius: 3
                       implicitWidth: demotableview.scrollBarWidth
                       color: demotableview.scrollBarColor
                   }
               }

               /*ScrollBar.horizontal: ScrollBar {
                   id: scroll_horizontal
                   anchors.bottom: parent.bottom
                   anchors.bottomMargin: 2
                   //active: table_view.ScrollBar.vertical.active
                   //policy: ScrollBar.AsNeeded
                   contentItem: Rectangle{
                       visible: (scroll_horizontal.size<1.0)
                       implicitHeight: demotableview.scrollBarWidth
                       color: demotableview.scrollBarColor
                   }
               }*/
               //model是在C++中定义的，和QtC++是类似的
               model: tableviewmodel
               delegate: Rectangle {

                    state: model.value["State"]

                    implicitHeight: 50
                    color: "transparent"
                    Rectangle {
                        anchors.top: parent.top;
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.leftMargin: (column !== 0) ? 0 : 20
                        anchors.rightMargin: (column !== table_view.columns - 1) ? 0 : 20
                        height: 1;
                        color: ProjectObject.lineColor;
                        visible: true
                    }
                    Rectangle {
                        anchors.bottom: parent.bottom;
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.leftMargin: (column !== 0) ? 0 : 20
                        anchors.rightMargin: (column !== table_view.columns - 1) ? 0 : 20
                        height: 1;
                        color: ProjectObject.lineColor;
                        visible: model.row === table_view.rows - 1
                    }

                    Loader {
                        id: itemLoader
                        anchors.centerIn: parent
                    }
                    Component {
                        id: textstate
                           Text {
                               id: tabletext
                               anchors.fill: parent
                               verticalAlignment: Text.AlignVCenter
                               horizontalAlignment: Text.AlignHCenter
                               visible: !parent.showImage

                               //获取单元格对应的值
                               text: model.value["Value"]
                               color: ProjectObject.defaultTextColor
                               font.family: ProjectObject.fontFamily
                               font.pixelSize: 18
                           }
                    }
                    Component {
                        id: buttonstate
                        Switch {
                            id: switchshowhighlight
                            anchors.centerIn: parent
                            width: 60
                            height: 36
                            checked: model.value["Value"]
                            indicator: Rectangle {
                                width: 60
                                height: 36
                                radius: height / 2
                                color: switchshowhighlight.checked ? ProjectObject.switchbuttonback_CheckColor : ProjectObject.switchbuttonback_DefaultColor
                                border.width: 2
                                border.color: ProjectObject.switchbuttonback_CheckColor

                                Rectangle {
                                    id: switchtransitioncircle
                                    x: 1
                                    width: parent.height - 2
                                    height: width
                                    radius: width / 2
                                    anchors.verticalCenter: parent.verticalCenter
                                    color: ProjectObject.switchbuttonCircle_Color
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
                                tableviewmodel.setData(tableviewmodel.index(row, column), switchshowhighlight.checked)
                                switchtransitioncircle.animationTo()
                                //catsidecolumn.showhighlight = visualPosition
                                //catsidecolumn.currentindex(catsidecolumn.listviewitem.currentIndex)
                            }
                        }
                    }

                    Component {
                        id: imagestate
                        Image {
                            id: imagetable
                            //anchors.centerIn: parent
                            source: ProjectObject.getCurrentResourcePath() + model.value["Value"]
                            width: sourceSize.width
                            height: sourceSize.height
                        }
                    }

                    states: [
                        State {
                            name: "Id"
                            PropertyChanges {
                                target: textstate

                            }
                            PropertyChanges {
                                target: itemLoader
                                sourceComponent: textstate
                            }
                        },
                        State {
                            name: "Button"
                            PropertyChanges {
                                target: buttonstate
                            }
                            PropertyChanges {
                                target: itemLoader
                                sourceComponent: buttonstate
                            }
                        },
                        State {
                            name: "Logo"
                            PropertyChanges {
                                target: imagestate
                            }
                            PropertyChanges {
                                target: itemLoader
                                sourceComponent: imagestate
                            }
                        },
                        State {
                            name: "String"
                            PropertyChanges {
                                target: textstate
                            }
                            PropertyChanges {
                                target: itemLoader
                                sourceComponent: textstate
                            }
                        }
                    ]

               }
           }

            //横项表头
            Item {
                id: header_horizontal
                anchors{
                    left: parent.left
                    right: parent.right
                    top: parent.top
                    topMargin: 30
                    //leftMargin: control.verHeaderWidth
                }
                height: demotableview.horHeaderHeight
                z: 2
                //暂存鼠标拖动的位置
                property int posXTemp: 0

                Row {
                    id: header_horizontal_row
                    anchors.fill: parent
                    leftPadding: -table_view.contentX
                    clip: true
                    spacing: 0

                    Repeater {
                        model: table_view.columns > 0 ? table_view.columns : 0

                        Rectangle {
                            id: header_horizontal_item
                            width: table_view.columnWidthProvider(index)+table_view.columnSpacing
                            height: demotableview.horHeaderHeight
                            color: "transparent"
                            Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: "#dddddd"; visible: model.row === table_view.rows - 1 }

                            Text {
                                color: ProjectObject.defaultTextColor
                                font.family: ProjectObject.fontFamily
                                font.pixelSize: 18
                                font.bold: true
                                anchors.centerIn: parent
                                text: headerHor[index] // tableviewmodel.headerData(index, Qt.Horizontal)
                            }

                        }

                    }
                }
            }



    }

    CatDropShadow {
        anchors.fill: tableback
        horizontalOffset: 0
        verticalOffset: 0
        radius: 10.0
        samples: 16
        color: ProjectObject.defaultShadowColor
        source: tableback
    }

}
