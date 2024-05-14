import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import CatTreeModel 1.0
import ModelTool 1.0
import "../../Common"
import "../../"

Rectangle {
    id: cattreelistview

    CatTreeModel {
        id: cattreemodel
        onShowMessage: {

        }
    }
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 5
        CatTreeHeader {
            id: cattreeheader
            Layout.preferredHeight: 40
            Layout.fillWidth: true
            height: 36
            treeModel: cattreemodel
            treeView: cattreeview
        }

        CatTreeView {
            id: cattreeview
            //width: cattreeheader.width
            sourceModel: cattreemodel
            clip: true

            Layout.fillHeight: true
            Layout.fillWidth: true

            onExpand: {
                cattreemodel.expand(index)
            }

            onCollapse: {
                cattreemodel.collapse(index)
            }

            onUpdatedemo: {
                demonstrationview.updatedemo(demoname, qmlsource)
            }


        }

    }

    Component.onCompleted: {
        let length = ProjectObject.defaultControl.control.length;
        console.log("length: " + length)
        var  params = {};
        /*for(let j = 0; j < ProjectObject.controlLibs.length; j++)
        {
            cattreeview.currentIndex = cattreemodel.addNode(-1, {"name": ProjectObject.controlLibs[j]})

            cattreeview.positionTo(-1)
            //let libs = String(ProjectObject.controlLibs[j])
            params[ProjectObject.controlLibs[j]] = 0;
        }*/
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
                //params[params[ProjectObject.defaultControl.control[i].libs]
                let searchlibs = cattreemodel.search("name", ProjectObject.defaultControl.control[i].libs)
                if(searchlibs.length <= 0)
                {
                    cattreemodel.addNode(-1, {"name": ProjectObject.defaultControl.control[i].libs});
                }

                searchlibs = cattreemodel.search("name", ProjectObject.defaultControl.control[i].libs)
                cattreemodel.addNode(searchlibs[0],
                                    {"name": ProjectObject.defaultControl.control[i].name,
                                     "author": ProjectObject.defaultControl.control[i].author,
                                     "version": ProjectObject.defaultControl.control[i].version,
                                     "logoSource": ProjectObject.defaultControl.control[i].logoSource,
                                     "qmlSource": ProjectObject.defaultControl.control[i].qmlSource,
                                     "libs": ProjectObject.defaultControl.control[i].libs})

            }
        }
        cattreeview.currentIndex = 1
        cattreeview.positionTo(cattreeview.currentIndex)
    }
}
