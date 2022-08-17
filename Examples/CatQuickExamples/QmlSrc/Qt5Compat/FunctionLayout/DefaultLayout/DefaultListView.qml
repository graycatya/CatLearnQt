import QtQuick 2.12
import QtQml 2.12

import GrayCatQtQuick 1.0
import "../../"

Rectangle {
    id: defaultlistview
    signal updateDemo(string demoname, string qmlsource)

    ListModel {
            id: listModel
    }

    ListView {
        id: listview
        anchors.fill: parent

        spacing: 10
        clip: true
        model: listModel

        delegate: Component {

            Rectangle {
                width: 300
                height: 100
                color: "transparent"

                DefaultListItem {
                    id: listitemrec
                    anchors.fill: parent
                    anchors.margins: 5
                    controlName: modelcontrolname
                    author: modelauthor
                    version: modelversion
                    logoSource: modellogosource
                    qmlSource: modelqmlsource
                    onOpencontrol: {
                        updateDemo(controlname, qmlsource)
                    }
                }

                function openDemo()
                {
                    listitemrec.openDemo()
                }
                /*
                Rectangle {
                    id: listitemrec
                    anchors.fill: parent
                    anchors.margins: 5
                    color: "#2C2C2C"
                    radius: 5
                }
                */
                CatDropShadow {
                    anchors.fill: listitemrec
                    horizontalOffset: 0
                    verticalOffset: 0
                    radius: 5.0
                    samples: 10
                    color: ProjectObject.defaultShadowColor
                    source: listitemrec
                }
            }
        }

        add: Transition {
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
        focus: true
    }

    Component.onCompleted: {

        let length = ProjectObject.defaultControl.control.length;
        console.log("length: " + length)
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
                listModel.append({
                     "modelcontrolname": ProjectObject.defaultControl.control[i].name,
                     "modelauthor": ProjectObject.defaultControl.control[i].author,
                     "modelversion": ProjectObject.defaultControl.control[i].version,
                     "modellogosource": ProjectObject.defaultControl.control[i].logoSource,
                     "modelqmlsource": ProjectObject.defaultControl.control[i].qmlSource,
                 });
            }
        }


    }
}
