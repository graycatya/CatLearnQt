import QtQuick 
import QtQuick.Layouts 
import QtQuick.Controls 
import QCatGrayQuick 

import QCatGrayChatStruct 
import QCatGrayQuickChatModel 
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
                    width: parent.width
                    height: delegate.item != null ? delegate.item.height : 0
                    chatmodel: catchatview.chatviewRepeaterModel
                    senderBgColor: ProjectObject.defaultButton_DefaultColor
                    recipientBgColor: ProjectObject.defaultButton_DefaultColor
                    delegate.source: ProjectObject.getProjectQmlControlPath() + "CatChatCommon/ChatItem.qml"

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
            ScrollView {
                id: chattextview
                anchors.fill: parent
                anchors.margins: 5
                anchors.bottomMargin: 40
                TextArea {
                    id: chattext
                    color: ProjectObject.controlNameColor
                    font.family: ProjectObject.fontFamily
                    font.pixelSize: 16
                    horizontalAlignment: TextEdit.AlignLeft
                    wrapMode: TextEdit.WrapAnywhere
                    selectByMouse: true
                    selectionColor: "black"
                    selectedTextColor: "white"
                    background: Rectangle{
                        color: "transparent"
                        radius: 5
                        border.color: ProjectObject.styleRectBorderColor
                    }

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
                        //catchatview.chatviewScrol.contentY = catchatview.chatviewScrol.contentHeight
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
                        //catchatview.chatviewScrol.contentY = catchatview.chatviewScrol.contentHeight
                    }
                }
            }
        }
    }
}
