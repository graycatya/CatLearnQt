import QtQuick 2.12
import CatTreeModel 1.0
import ModelTool 1.0
import QtQuick.Layouts 1.12
import QCatGrayQuick 1.0
import "../Common"
import "../"
import "./CatTableViewCommon"

import com.catgray.QCatGrayQuickTableViewModelStruct 1.0
import com.catgray.QCatGrayQuickTableViewHeaderStruct 1.0


Item {
    id: democattableview

    CatTableView {
        id: cattableview
        anchors.fill: parent
        anchors.topMargin: 50
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.bottomMargin: 20
        freezeHeader: false
        columnfreezeNum: 1
        leftbottomfreezeNum: 0
        headerData: ["check", "id", "name", "time", "uuid", "load"]

        headerDelegate: CatTableViewHeaderDelegateBase {
            sourceComponent: isheaderFreeze ? headerComponent : itemComponent
        }

        delegate: QuickWidgetTableDataItem {
                border.color: "#FFFFFF"
                border.width: 1
                color: "#000000"
        }

        Component {
            id: headerComponent
            QuickWidgetTableHeaderItem {
                border.color: "#FFFFFF"
                border.width: 1
                color: "#000000"
            }
        }

        Component {
            id: itemComponent
            QuickWidgetTableDataItem {
                border.color: "#FFFFFF"
                border.width: 1
                color: "#000000"
            }
        }

        Component.onCompleted: {
            settingTableView();
            initTableView();

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

    // Timer {
    //     interval: 1000
    //     repeat: true
    //     running: true
    //     onTriggered: {
    //         var currentTime = new Date()
    //         cattableview.model.appendStruct({"check": false, "id":cattableview.model.tabledata.length, "name":"user"+cattableview.model.tabledata.length, "time": currentTime.toString("yyyy-MM-dd hh:mm:ss:fff"), "uuid": "uuid" + cattableview.model.tabledata.length, "load": 0.2});
    //     }
    // }

    function initTableView() {
        for(var i = 0; i < 1000; i++)
        {
            var currentTime = new Date()
            cattableview.model.appendStruct({"check": false, "id":i, "name":"user"+i, "time": currentTime.toString("yyyy-MM-dd hh:mm:ss:fff"), "uuid": "uuid" + i, "load": 0.2});
        }
    }

}
