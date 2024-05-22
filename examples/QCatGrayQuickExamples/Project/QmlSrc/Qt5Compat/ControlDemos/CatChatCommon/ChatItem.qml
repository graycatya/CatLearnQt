import QtQuick 2.12
import QCatGrayQuick 1.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import "../../"

Item {
    id: root

    property var loaderparent: parent.parent
    height: rootColumn.implicitHeight + timeeditrow.implicitHeight + 5

    Connections {
        target: loaderparent.chatmodel.getStruct(index)
        function onSenderimageChanged() {
            image.source = model.senderimage
        }

        function onRecipientimageChanged() {
            image.source = model.recipientimage
        }

    }



    Column {
        id: rootColumn
        anchors.left: parent.left
        anchors.right: parent.right
        height: rowlayout.implicitHeight
        spacing: 5
        Row {
            id: rowlayout
            //anchors.fill: parent
            width: loaderparent.width
            spacing: 15
            layoutDirection: loaderparent.isUser ? Qt.LeftToRight : Qt.RightToLeft
            Image {
                id: image
                width: 40
                height: 40
                source: model.senderimage !== "" ? model.senderimage : model.recipientimage
            }
            Rectangle {
                id: textRectangle
                width: textedit.contentWidth
                height: textedit.height
                color: loaderparent.isUser ? loaderparent.senderBgColor : loaderparent.recipientBgColor
                radius: 5
                Rectangle{
                    id: bubblerect
                    width: 10
                    height: 10
                    anchors.horizontalCenter: loaderparent.isUser ? parent.left : parent.right
                    y: 48/2 - 10
                    rotation: 45
                    color: loaderparent.isUser ? loaderparent.senderBgColor : loaderparent.recipientBgColor
                }
                CatChatTextEdit {
                    id: textedit
                    font.family: ProjectObject.fontFamily
                    font.pixelSize: 14
                    color: ProjectObject.defaultTextColor

                    verticalAlignment: TextEdit.AlignVCenter
                    horizontalAlignment: TextEdit.AlignLeft
                    readOnly: true
                    selectByMouse: true
                    selectionColor: "black"
                    selectedTextColor: "white"
                    wrapMode: TextEdit.WrapAnywhere
                    padding: 14

                    text: model.data
                    property int contentWidth: Math.max(10,loaderparent.width - 50*2)
                    width: Math.min(contentWidth, textWidth)
                }
            }
        }

    }
    Row {
        id: timeeditrow
        anchors.top: rootColumn.bottom
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: rowlayout.spacing + image.width
        anchors.rightMargin: rowlayout.spacing + image.width
        layoutDirection: loaderparent.isUser ? Qt.LeftToRight : Qt.RightToLeft
        CatChatTextEdit {
            id: timeedit
            font.family: ProjectObject.fontFamily
            font.pixelSize: 14
            color: ProjectObject.defaultTextColor

            verticalAlignment: TextEdit.AlignVCenter
            horizontalAlignment: TextEdit.AlignLeft
            readOnly: true
            selectByMouse: true
            selectionColor: "black"
            selectedTextColor: "white"
            wrapMode: TextEdit.WrapAnywhere
            padding: 0
    //                    text: model.datetime
           text: {
                var date = new Date(model.datetime);
                return date.toLocaleString(Qt.locale("de_DE"), "yyyy-MM-dd HH:mm:ss")
            }
        }
    }

}
