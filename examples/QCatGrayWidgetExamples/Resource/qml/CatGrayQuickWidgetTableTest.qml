import QtQuick 2.12
import QtQuick.Controls 2.12
import QCatGrayQuick 1.0
import com.catgray.QCatGrayQuickTableViewModelStruct 1.0

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
        //width: 120
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
        headerData: ["check", "id", "name", "time", "uuid", ""]

        headerDelegate: CatTableViewHeaderDelegateBase {
            width: 200
            height: 30
            Rectangle {
                anchors.fill: parent
                border.color: "#FFFFFF"
                border.width: 1
                color: "#000000"
                Component.onCompleted: {
                    console.log("isheaderFreeze: " + isheaderFreeze)
                }
            }
        }
        delegate: CatTableViewDelegateBase {

            delegate : Rectangle {
                width: 200
                height: 30
                border.color: "#FFFFFF"
                border.width: 1
                color: "#000000"
            }
            Component.onCompleted: {
                console.log("init: " + index)
                console.log("key : " + cattableview.model.getStruct(index).data["key"]);
                console.log("columnCount: " + cattableview.model.columnCount())
            }
        }

        Component.onCompleted: {
            cattableview.model.setHeaderCount(5);
            for(var i = 0; i < 20; i++)
                cattableview.model.appendStruct({"id":"test"});

        }
    }

    onUpdateStyle: function(index) {
        console.log("onUpdateStyle: " + index)
        StyleConfig.currentTheme = index;
    }
}
