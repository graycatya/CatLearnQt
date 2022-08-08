import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import GrayCatQtCompat 1.0
import "../../"

Rectangle {
    id: defaultlayout
    color: "transparent"

    RowLayout {
        id: defaultRowlayout
        anchors.fill: parent
        spacing: 20
        Rectangle {
            Layout.preferredWidth: 300
            Layout.fillHeight: true
            color: "transparent"
            CatTreeListView {
                id: cattreelistview
                anchors.fill: parent
                color: ProjectObject.defaultRectangleColor
                radius: 5
            }

            CatDropShadow {
                anchors.fill: cattreelistview
                horizontalOffset: 0
                verticalOffset: 0
                radius: 5.0
                samples: 10
                color: ProjectObject.defaultShadowColor
                source: cattreelistview
            }
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"
            CatTreeDemoStrationView {
                id: demonstrationview
                anchors.fill: parent
                //anchors.margins: 5
                radius: 5
                color: ProjectObject.defaultRectangleColor
            }
            CatDropShadow {
                anchors.fill: demonstrationview
                horizontalOffset: 0
                verticalOffset: 0
                radius: 5.0
                samples: 10
                color: ProjectObject.defaultShadowColor
                source: demonstrationview
            }
        }
    }

    /*function updatedemo(demoname, index, qmlsource)
    {
        demonstrationview.updatedemo(demoname, index, qmlsource)
    }*/
}
