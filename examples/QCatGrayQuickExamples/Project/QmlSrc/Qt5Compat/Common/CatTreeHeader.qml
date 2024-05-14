import QtQuick 2.12
import QCatGrayQuick 1.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "../"

Item {
    id: cattreeheader
    property var treeView
    property var treeModel

    RowLayout {
        anchors.fill: parent
        spacing: 5

        GeneralInput {
            id: searchInput
            property var searchHitList: []
            property int current: 0
            property int count: 0
            Layout.fillHeight: true
            Layout.fillWidth: true
            backgroudItem.radius: 6
            backgroudItem.color: "#01000000"
            backgroudItem.border.width: 1
            backgroudItem.border.color: textInput.cursorVisible
                                        ? ProjectObject.defaultGeneralInputBackgroundBorderColor_hovered
                                        : searchInput.hovered
                                          ? ProjectObject.defaultGeneralInputBackgroundBorderColor_hovered
                                          : ProjectObject.defaultGeneralInputBackgroundBorderColor

            //logoImage.source: "qrc:/Images/png/domaininput.png"
            //logoImageSize: 18

            textInput.color: ProjectObject.defaultTextColor
            textInput.font.pixelSize: 14
            //textInputMargin: -6
            textInput.font.family: ProjectObject.fontFamily
            //textInputText: "test"
            //textInput.placeholderText: qsTr("Search")
            //textInput.placeholderTextColor: "#93A9BE"
            textInput.selectionColor: ProjectObject.defaultGeneralInputSelectionColor
            textInput.selectedTextColor: ProjectObject.defaultTextColor
            comboboxButton.btnImgUrl: ProjectObject.getCurrentResourcePath() + "SearchInput.png"
            comboboxButtonSize: 26
            layoutRow.anchors.rightMargin: 7
            comboboxButton.onClicked: {
                console.log("search: " + textInputText)
                if(textInputText.length > 0)
                {
                    searchHitList = treeModel.search("name", textInputText)
                    count = searchHitList.length
                    current = 0
                } else {
                    searchHitList = []
                    count = 0
                    current = 0
                }
                updatePos()
            }
            //comboboxButton.btnImgNormal: ""

        }

        ColumnLayout {
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40
            spacing: 4
            CatButtonImage {
                id: lastButton
                Layout.preferredHeight: 15
                Layout.preferredWidth: 16
                Layout.alignment: Qt.AlignHCenter
                btnImgUrl: ProjectObject.getCurrentResourcePath() + "last_triangle.png"

                onClicked: {
                    if (searchInput.count > 0) {
                        searchInput.current = (searchInput.count + searchInput.current - 1) % searchInput.count
                        updatePos()
                    }
                }
            }

            CatButtonImage {
                id: nextButton
                Layout.preferredHeight: 15
                Layout.preferredWidth: 16
                Layout.alignment: Qt.AlignHCenter
                btnImgUrl: ProjectObject.getCurrentResourcePath() + "next_triangle.png"

                onClicked: {
                    if (searchInput.count > 0) {
                        searchInput.current = (searchInput.current + 1) % searchInput.count
                        updatePos()
                    }
                }

            }
        }

    }

    function updatePos() {
        if (searchInput.current >= 0 && searchInput.current < searchInput.count) {
            treeModel.expandTo(searchInput.searchHitList[searchInput.current])
            treeView.currentIndex = searchInput.searchHitList[searchInput.current]
            treeView.positionTo(searchInput.searchHitList[searchInput.current])
        }
    }
}
