import QtQuick 2.12
import QtQuick.Controls 2.12
import QCatGrayQuick 1.0
import com.catgray.QCatGrayQuickTableViewModelStruct 1.0
import com.catgray.QCatGrayQuickTableViewHeaderStruct 1.0

Rectangle {
    id: root

    signal updateStyle(int index)

    color: StyleConfig.backColor


    CatFps {
        id: catfps
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 5
        anchors.topMargin: 5
        gradient0Color: StyleConfig.fpsgradient0Color
        gradient1Color: StyleConfig.fpsgradient1Color
        height: 32
    }

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
            datamodel: cattableview.model
            headerStruct: cattableview.model.getHeaderStruct(rowIndex)
            headerTableData: cattableview.model.headerTableData
            Rectangle {
                width: headerStruct.preferredWidth
                height: datamodel.preferredHeaderHeight

                border.color: StyleConfig.tableviewItem_borderColor
                border.width: 1
                color: StyleConfig.tableviewHeader_backColor
                Text {
                   anchors.fill: parent
                   verticalAlignment: Text.AlignVCenter
                   horizontalAlignment: Text.AlignHCenter
                   text: datamodel.headerTableData[index]
                   color: StyleConfig.textColor
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
            initTableView();
            testTimer.running = true

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
         interval: 5000
         //repeat: true
         //running: true
         onTriggered: {
             console.log("cattableview: " + cattableview.model.tabledata.length)
             cattableview.model.removeStruct(20);
             console.log("cattableview: " + cattableview.model.tabledata.length)
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

    onUpdateStyle: function(index) {
        console.log("onUpdateStyle: " + index)
        StyleConfig.currentTheme = index;
    }
}
