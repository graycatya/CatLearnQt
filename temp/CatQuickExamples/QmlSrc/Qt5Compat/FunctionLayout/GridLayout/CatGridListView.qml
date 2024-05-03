import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQml.Models 2.12
import QtQuick.Layouts 1.12
import "../../"

Item {
    id: catgridlistview

    ObjectModel {
        id: gridviewmodel
    }


    GridView {
        id: gridview

        cellWidth: 320
        cellHeight: 440

        anchors.fill: parent

        clip: true

        model: gridviewmodel

        /*add: Transition {
            NumberAnimation { property: "opacity";
                from: 0; to: 1.0; duration: 400 }
            NumberAnimation { property: "scale";
                from: 0; to: 1.0; duration: 400 }
        }

        // 解决快速添加问题
        displaced: Transition {
            NumberAnimation { properties: "x,y"; duration: 400; easing.type: Easing.OutBounce }

            // 确保opacity和scale值变为1.0
            NumberAnimation { property: "opacity"; to: 1.0 }
            NumberAnimation { property: "scale"; to: 1.0 }
        }

        focus: true*/

    }



    onWidthChanged: {
        console.log("width: " + width)
        console.log("(width / 320)*320: " + Math.floor(width / 320)*320)
        let gridMargin = width - Math.floor(width / 320)*320;
        console.log("gridMargin: " + gridMargin)
        gridview.anchors.leftMargin = gridMargin / 2
        gridview.anchors.rightMargin = gridMargin / 2

    }

    Component.onCompleted: {
        let length = ProjectObject.defaultControl.control.length;
        for(let i = 0; i < length; i++)
        {
            let add = true;
            if(!catconfig.qtQuick3D() && ProjectObject.defaultControl.control[i].libs === "quick3d")
            {
                add = false;
            } else if(!catconfig.qtWebEngine() && ProjectObject.defaultControl.control[i].libs === "webengine")
            {
                add = false;
            }

            if(add)
            {
                let item = Qt.createComponent("qrc:/FunctionLayout/GridLayout/CatGridListItem.qml")
                gridviewmodel.insert(gridview.model.count, item.createObject(gridview));
                gridviewmodel.get(gridview.model.count - 1).controlName = ProjectObject.defaultControl.control[i].name
                gridviewmodel.get(gridview.model.count - 1).author = ProjectObject.defaultControl.control[i].author
                gridviewmodel.get(gridview.model.count - 1).version = ProjectObject.defaultControl.control[i].version
                gridviewmodel.get(gridview.model.count - 1).logoSource = ProjectObject.defaultControl.control[i].logoSource
                gridviewmodel.get(gridview.model.count - 1).qmlSource = ProjectObject.defaultControl.control[i].qmlSource
                gridview.positionViewAtEnd();
            }
            gridview.positionViewAtBeginning();
        }
    }

}
