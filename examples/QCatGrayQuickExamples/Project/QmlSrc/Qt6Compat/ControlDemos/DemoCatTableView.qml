import QtQuick 
import CatTreeModel 
import ModelTool 
import QtQuick.Layouts 
import QCatGrayQuick 
import "../Common"
import "../"
import "./CatTableViewCommon"

import com.catgray.QCatGrayQuickTableViewModelStruct 
import com.catgray.QCatGrayQuickTableViewHeaderStruct 


Item {
    id: democattableview

    CatTableView {
        id: cattableview
        anchors.fill: parent
        anchors.topMargin: 10
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.bottomMargin: 50
        freezeHeader: false
        columnfreezeNum: 1
        leftbottomfreezeNum: 0
        headerData: ["check", "id", "name", "time", "uuid", "load"]

        headerDelegate: CatTableViewHeaderDelegateBase {
            datamodel: cattableview.model
            headerStruct: cattableview.model.getHeaderStruct(rowIndex)
            headerTableData: cattableview.model.headerTableData
            Rectangle {
                width: headerStruct.preferredWidth
                height: datamodel.preferredHeaderHeight

                border.color: ProjectObject.lineColor
                border.width: 1
                color: ProjectObject.defaultRectangleColor
                Text {
                   anchors.fill: parent
                   verticalAlignment: Text.AlignVCenter
                   horizontalAlignment: Text.AlignHCenter
                   text: datamodel.headerTableData[index]
                   color: ProjectObject.defaultTextColor
                   font.pixelSize: 16

                }

            }

        }

        delegate: QuickWidgetTableDataItem {
            columnIndex: index
            datamodel: cattableview.model
        }

        Component.onCompleted: {
            settingTableView();
            //initTableView();
            //testTimer.running = true

        }
    }

    RowLayout {
        anchors.top: cattableview.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 5
        CatButton {
            id: asendbutton
            Layout.fillHeight: true
            Layout.preferredWidth: 80
            background: Rectangle {
                anchors.fill: parent
                radius: 5

                color: ProjectObject.defaultButton_DefaultColor
                border.width: parent.hovered ? 1 : 0
                border.color: ProjectObject.styleRectBorderColor

                CatBasicsText {
                    anchors.fill: parent
                    font.family: ProjectObject.fontFamily
                    font.pixelSize: 14
                    color: ProjectObject.defaultTextColor
                    text: "Add"
                }
            }

            onClicked: {
                var currentTime = new Date()
                cattableview.model.appendStruct({"check": false, "id": cattableview.model.tabledata.length,
                                                    "name":"user"+cattableview.model.tabledata.length,
                                                    "time": currentTime.toString("yyyy-MM-dd hh:mm:ss:fff"),
                                                    "uuid": "uuid" + cattableview.model.tabledata.length, "load": 0.2});
            }
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        CatButton {
            id: bsendbutton
            Layout.fillHeight: true
            Layout.preferredWidth: 80
            background: Rectangle {
                anchors.fill: parent
                radius: 5

                color: ProjectObject.defaultButton_DefaultColor
                border.width: parent.hovered ? 1 : 0
                border.color: ProjectObject.styleRectBorderColor

                CatBasicsText {
                    anchors.fill: parent
                    font.family: ProjectObject.fontFamily
                    font.pixelSize: 14
                    color: ProjectObject.defaultTextColor
                    text: "Remove"
                }
            }

            onClicked: {
                cattableview.model.removeStruct(cattableview.model.tabledata.length-1);
            }
        }
    }

    function settingTableView() {
        //cattableview.model.setHeaderCount(5);
        cattableview.model.setAllHeaderMaximumWidth(200);
        cattableview.model.setAllHeaderPreferredWidth(200);
        cattableview.model.getHeaderStruct(2).resizeMode = QCatGrayQuickTableViewHeaderStruct.Stretch
        cattableview.model.getHeaderStruct(2).maximumWidth = 1000
        cattableview.model.getHeaderStruct(4).resizeMode = QCatGrayQuickTableViewHeaderStruct.Stretch
        cattableview.model.getHeaderStruct(4).maximumWidth = 1000
        cattableview.model.getHeaderStruct(3).resizeMode = QCatGrayQuickTableViewHeaderStruct.FixedCanBeManuallyAdjusted
    }

     Timer {
         id: testTimer
         interval: 1000
         repeat: true
         running: false
         onTriggered: {
             var currentTime = new Date()
             cattableview.model.appendStruct({"check": false, "id": cattableview.model.tabledata.length,
                                                 "name":"user"+cattableview.model.tabledata.length,
                                                 "time": currentTime.toString("yyyy-MM-dd hh:mm:ss:fff"),
                                                 "uuid": "uuid" + cattableview.model.tabledata.length, "load": 0.2});
             // console.log("cattableview: " + cattableview.model.tabledata.length)
             // cattableview.model.removeStruct(20);
             // console.log("cattableview: " + cattableview.model.tabledata.length)
//             var currentTime = new Date()
//             cattableview.model.appendStruct({"check": false, "id":cattableview.model.tabledata.length, "name":"user"+cattableview.model.tabledata.length, "time": currentTime.toString("yyyy-MM-dd hh:mm:ss:fff"), "uuid": "uuid" + cattableview.model.tabledata.length, "load": 0.2});
         }
     }

    function initTableView() {
        for(var i = 0; i < 100; i++)
        {
            var currentTime = new Date()
            cattableview.model.appendStruct({"check": false, "id":i, "name":"user"+i, "time": currentTime.toString("yyyy-MM-dd hh:mm:ss:fff"), "uuid": "uuid" + i, "load": 0.2});
        }
    }

}
