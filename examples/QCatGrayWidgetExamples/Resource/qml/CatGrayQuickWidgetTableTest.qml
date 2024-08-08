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
        columnfreezeNum: 1
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

    function initTableView() {
        for(var i = 0; i < 50; i++)
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
