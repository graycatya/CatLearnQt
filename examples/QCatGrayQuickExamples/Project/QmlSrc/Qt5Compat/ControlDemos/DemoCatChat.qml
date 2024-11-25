import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QCatGrayQuick 1.0

import QCatGrayChatStruct 1.0
import QCatGrayQuickChatModel 1.0
import "../"
Item {
    id: root


    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        QCatGrayQuickChatModel {
            id: chatmodel
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            border.width: 1
            border.color: ProjectObject.styleRectBorderColor
            color: "transparent"
            radius: 5
            CatChatView {
                id: catchatview
                chatviewRepeaterModel: chatmodel
                anchors.fill: parent
                anchors.margins: 10
                clip: true
                chatviewDelegate: CatChatItemBase {
                    width: catchatview.width
                    height: delegate.item.height
                    chatmodel: catchatview.chatviewRepeaterModel
                    senderBgColor: ProjectObject.defaultButton_DefaultColor
                    recipientBgColor: ProjectObject.defaultButton_DefaultColor
                    delegate.source: "CatChatCommon/ChatItem.qml"

                }

                chatviewRepeater.onCountChanged: {
                    console.log("update model")
                }
            }
        }
        Rectangle {
            Layout.fillHeight: true
            Layout.minimumHeight: 150
            Layout.maximumHeight: 150
            Layout.fillWidth: true
            border.width: 1
            border.color: ProjectObject.styleRectBorderColor
            color: "transparent"
            radius: 5
            Flickable  {
                id: chattextview
                anchors.fill: parent
                anchors.margins: 5
                anchors.bottomMargin: 40
                contentWidth: chattext.contentWidth
                contentHeight: chattext.contentHeight
                clip: true
                function ensureVisible(r)
                  {
                      if (contentX >= r.x)
                          contentX = r.x;
                      else if (contentX+width <= r.x+r.width)
                          contentX = r.x+r.width-width;
                      if (contentY >= r.y)
                          contentY = r.y;
                      else if (contentY+height <= r.y+r.height)
                          contentY = r.y+r.height-height;
                  }

                TextEdit {
                    id: chattext
                    width: chattextview.width
                    color: ProjectObject.controlNameColor
                    font.family: ProjectObject.fontFamily
                    font.pixelSize: 16
                    horizontalAlignment: TextEdit.AlignLeft
                    wrapMode: TextEdit.WrapAnywhere
                    onCursorRectangleChanged: chattextview.ensureVisible(cursorRectangle)
                    selectByMouse: true
                    selectionColor: "black"
                    selectedTextColor: "white"
                    // background: Rectangle{
                    //     color: "transparent"
                    //     radius: 5
                    //     border.color: ProjectObject.styleRectBorderColor
                    // }

                    text: "There was a boy named Tom, who was born into a poor family, but he possessed a resilient character and diligent qualities. Despite the difficult circumstances, Tom never gave up his pursuit of knowledge. He used every spare moment to study, constantly enriching himself. Eventually, through hard work and perseverance, he obtained an excellent job and changed his own and his family’s destiny. This story tells us that no matter what situation we are in, as long as we have firm beliefs and unwavering efforts, we can overcome difficulties and strive for success."
                }
            }
            RowLayout {
                anchors.top: chattextview.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.margins: 5
                CatButton {
                    id: asendbutton
                    Layout.fillHeight: true
                    Layout.preferredWidth: 80
                    background: Rectangle {
                        anchors.fill: parent
                        radius: 5

                        color: ProjectObject.defaultButton_DefaultColor
                        border.width: parent.hovered ? 1 : 0
                        border.color: ProjectObject.styleRectBorderColor

                        CatBasicsText {
                            anchors.fill: parent
                            font.family: ProjectObject.fontFamily
                            font.pixelSize: 14
                            color: ProjectObject.defaultTextColor
                            text: "A Send"
                        }
                    }

                    onClicked: {
                        var currentDatetime = parseInt(new Date().getTime())
                        var object = chatmodel.appendStruct(currentDatetime, "A", "A", "B", currentDatetime,
                                                            chattext.text, ChatStruct.Chat_Text)
                        object.senderimage = ProjectObject.getCurrentResourcePath() + "Chat.png"
                        catchatview.chatviewScrol.position = 1
                    }
                }

                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }

                CatButton {
                    id: bsendbutton
                    Layout.fillHeight: true
                    Layout.preferredWidth: 80
                    background: Rectangle {
                        anchors.fill: parent
                        radius: 5

                        color: ProjectObject.defaultButton_DefaultColor
                        border.width: parent.hovered ? 1 : 0
                        border.color: ProjectObject.styleRectBorderColor

                        CatBasicsText {
                            anchors.fill: parent
                            font.family: ProjectObject.fontFamily
                            font.pixelSize: 14
                            color: ProjectObject.defaultTextColor
                            text: "B Send"
                        }
                    }

                    onClicked: {
                        var currentDatetime = parseInt(new Date().getTime())
                        var object = chatmodel.appendStruct(currentDatetime, "A", "B", "A", currentDatetime,
                                                            chattext.text, ChatStruct.Chat_Text)
                        object.recipientimage = ProjectObject.getCurrentResourcePath() + "Chat.png"
                        catchatview.chatviewScrol.position = 1
                    }
                }
            }
        }
    }
}
