import QtQuick 2.12
import GrayCatQtQuick 1.0
import QtQuick.Controls 2.12
import "../"

Item {
    id: cattreeheader

    GeneralInput {
        id: searchInput
        anchors.fill: parent
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
        textInputText: "test"
        //textInput.placeholderText: qsTr("Search")
        //textInput.placeholderTextColor: "#93A9BE"
        textInput.selectionColor: ProjectObject.defaultGeneralInputSelectionColor
        textInput.selectedTextColor: ProjectObject.defaultTextColor

        //comboboxButton.btnImgNormal: ""

    }
}
