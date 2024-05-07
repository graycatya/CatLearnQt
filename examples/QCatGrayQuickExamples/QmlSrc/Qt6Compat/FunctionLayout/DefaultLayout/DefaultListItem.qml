import QtQuick
import QtQml
import QtQuick.Layouts
import QCatGrayQuick
import "../../"


Rectangle {
    id: defaultlistitem
    property string controlName: "------"
    property string author: "------"
    property string version: "------"
    property string logoSource: ""
    property string qmlSource: ""
    signal opencontrol(string controlname, string qmlsource)
    anchors.fill: parent
    anchors.margins: 5
    color: ProjectObject.controlRectangleColor
    radius: 5
    height: 100



    Image {
        id: itemlogo
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 15
        anchors.leftMargin: 25
        source: ProjectObject.getCurrentResourcePath() + logoSource
        width: 30
        height: 30
    }

    Text {
        id: controlnametext
        anchors.top: parent.top
        anchors.left: itemlogo.right
        anchors.topMargin: 15
        anchors.leftMargin: 10
        font.bold: true
        height: 30
        font.family: ProjectObject.fontFamily
        text: defaultlistitem.controlName
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 14
        color: ProjectObject.controlNameColor
    }

    CatButtonImage {
        id: openControl
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 15
        anchors.rightMargin: 25
        width: 30
        height: 30
        backImage.width: backImage.sourceSize.width
        backImage.height: backImage.sourceSize.height
        btnImgNormal: ProjectObject.getCurrentResourcePath() + "Demonstrate.svg"
        btnImgHovered: ProjectObject.getCurrentResourcePath() + "Demonstrate.svg"
        btnImgPressed: ProjectObject.getCurrentResourcePath() + "Demonstrate.svg"
        btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "Demonstrate.svg"
        backgroundColor: "#1D9FF7"
        backgroundColor_hovered: "#1D9FF7"
        backgroundColor_pressed: "#1D9FF7"
        imagebackground.border.width: openControl.hovered ? 1 : 0
        imagebackground.border.color: "#1171AE"
        imagebackground.radius: 5
        onClicked: {
            opencontrol(controlName, qmlSource);
        }
    }

    Text {
        id: authortext
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.bottomMargin: 15
        anchors.leftMargin: 25
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.bold: true
        text: qsTr("Author: %1").arg(defaultlistitem.author)
        font.pixelSize: 12
        color: ProjectObject.controlAuthorColor
    }

    Text {
        id: versiontext
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: 15
        anchors.rightMargin: 25
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.bold: true
        text: qsTr("Version: %1").arg(defaultlistitem.version)
        font.pixelSize: 12
        color: ProjectObject.controlVersionColor
    }

    function setControlDemo()
    {
        opencontrol(controlName, qmlSource);
    }

}
