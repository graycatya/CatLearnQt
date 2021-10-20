import QtQuick 2.12
import QtQuick.Controls 2.12
import GrayCatQtQuick 1.0
import "../"

Item {
    id: cattreeview

    readonly property string __modelDepthKey: "TreeModel_depth"
    readonly property string __modelExpendKey: "TreeModel_expend"
    readonly property string __modelChildrenExpendKey: "TreeModel_childrenExpend"
    readonly property string __modelHasChildrendKey: "TreeModel_hasChildren"

    readonly property string __modelParentKey: "ModelParentKey"
    readonly property string __modelChildrenKey: "ModelChildrenKey"

    property alias sourceModel: listview.model
    property int basePadding: 8
    property int subPadding: 20
    property alias currentIndex: listview.currentIndex
    property alias header: listview.header
    property alias treeListView: listview

    signal collapse(int index);
    signal expand(int index);

    ListView {
        id: listview
        anchors.fill: parent
        currentIndex: -1

        delegate: Rectangle {
            id: delegateRect
            width: 300
            height: model.display[__modelExpendKey] === true ? 36 : 0
            visible: height > 0
            color: (listview.currentIndex === index || cattransarea.hovered) ? ProjectObject.catsidecolumnitem_SelectColor : "transparent"
            radius: 5
            Image {
                id: controlTreeImage
                anchors {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: cattreeview.basePadding + model.display[__modelDepthKey] * cattreeview.subPadding
                }

                visible: model.display[__modelHasChildrendKey]
                source: model.display[__modelChildrenExpendKey]
                        ? ProjectObject.getCurrentResourcePath() + "TreeButton_fold_default.png"
                        : ProjectObject.getCurrentResourcePath() + "TreeButton_unfold_default.png"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(model.display[__modelHasChildrendKey])
                        {
                            if(true === model.display[__modelChildrenExpendKey])
                            {
                                collapse(index)
                            } else {
                                expand(index)
                            }
                        }
                    }
                }
            }

            CatTransArea {
                id: cattransarea
                height: parent.height
                width: parent.width - controlTreeImage.x
                hoverEnabled: true
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                //enabled: !delegateRect.e
                onPressed: {
                    if (listview.currentIndex !== index) {
                        listview.currentIndex = index;
                    } else {
                        listview.currentIndex = -1;
                    }
                    console.log("treeitem clicked: " + model.display["name"])
                }

            }

            CatBasicsText {
                id: catbasicsText
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: controlTreeImage.right
                anchors.leftMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10
                horizontalAlignment: Text.AlignLeft
                text: model.display["name"]
                font.pixelSize: 14
                font.family: ProjectObject.fontFamily
                color: ProjectObject.defaultTextColor
            }

        }

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
        if (listview.currentItem) {
            listview.currentItem.editable = !listview.currentItem.editable
        }
    }
    function positionTo(index) {
        listview.positionViewAtIndex(index, ListView.Center)
    }

}
