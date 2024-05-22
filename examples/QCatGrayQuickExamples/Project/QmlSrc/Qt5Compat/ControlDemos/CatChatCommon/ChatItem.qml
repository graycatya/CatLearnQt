import QtQuick 2.12
import QCatGrayQuick 1.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import "../../"

Item {
    id: root

    property var loaderparent: parent.parent
    height: rootColumn.implicitHeight

    Connections {
        target: model
        function onSenderimageChanged() {
            console.log("model.senderimage: " + model.senderimage)
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
            }
            Rectangle {
                id: textRectangle
                width: textedit.contentWidth
                height: textedit.height
                color: loaderparent.isUser ? loaderparent.senderBgColor : loaderparent.recipientBgColor
                radius: 5
                Rectangle{
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



}
