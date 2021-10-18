import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    id: cattreeview

    readonly property string __modelDepthKey: "TreeModel_depth"
    readonly property string __modelExpendKey: "TreeModel_expend"
    readonly property string __modelChildrenExpendKey: "TreeModel_childrenExpend"
    readonly property string __modelHasChildrendKey: "TreeModel_hasChildren"

    readonly property string __modelParentKey: "ModelParentKey"
    readonly property string __modelChildrenKey: "ModelChildrenKey"

    property alias sourceModel: listView.model
    property int basePadding: 4
    property int subPadding: 8
    property alias currentIndex: listView.currentIndex
    property alias header: listView.header
    property alias treeListView: listView

    signal collapse(int index);
    signal expand(int index);

    ListView {
        id: listview
        anchors.fill: parent
        currentIndex: -1

        add: Transition {
            NumberAnimation  { from: -root.width; to: 0; properties: "x"; duration: 300; easing.type: Easing.OutQuad }
        }
        remove: Transition {
            NumberAnimation { to: -root.width; property: "x"; duration: 300; easing.type: Easing.OutQuad }
        }
        displaced : Transition {
            NumberAnimation  { properties: "x,y"; duration: 300; easing.type: Easing.OutQuad }
        }

        ScrollIndicator.vertical: ScrollIndicator { }

    }

    function rename(index) {
        if (listView.currentItem) {
            listView.currentItem.editable = !listView.currentItem.editable
        }
    }
    function positionTo(index) {
        listView.positionViewAtIndex(index, ListView.Center)
    }

}
