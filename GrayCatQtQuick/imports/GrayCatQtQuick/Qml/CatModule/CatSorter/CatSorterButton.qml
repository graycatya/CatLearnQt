import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12
import QtQml.Models 2.12
import QtQuick.Controls 2.12

Item {
    id: catsorterbutton
    property int page: 0

    clip: true

    signal previousPage()
    signal nextPage()
    signal updatePage(int page)

    property int itemSize: catsorter.itemSize
    property int spacing: catsorter.itemSpacing

    enum State {
        PreviousButton,
        NextButton,
        UpdatepagetextButton,
        PreviousSkitpageButton,
        NextSkitpageButton
    }

    property int buttonState: CatSorterButton.PreviousButton


    width: itemSize + spacing
    height: itemSize

    Loader {
        id: sorterbutton

        anchors.fill: parent
        anchors.leftMargin: spacing
        clip: true

        visible: status == Loader.Ready
    }

    states: [
        State {
            name: "previousbutton"
            PropertyChanges {
                target: sorterbutton
                source: "qrc:/GrayCatQtQuick/Qml/CatModule/CatSorter/UpdatePageButton.qml";
            }
            PropertyChanges {
                target: catsorterbutton
                buttonState: CatSorterButton.PreviousButton
            }
        },
        State {
            name: "nextbutton"
            PropertyChanges {
                target: sorterbutton
                source: "qrc:/GrayCatQtQuick/Qml/CatModule/CatSorter/UpdatePageButton.qml";
            }
            PropertyChanges {
                target: catsorterbutton
                buttonState: CatSorterButton.NextButton
            }
        },
        State {
            name: "updatepagetextbutton"
            PropertyChanges {
                target: sorterbutton
                source: "qrc:/GrayCatQtQuick/Qml/CatModule/CatSorter/UpdatePageTextButton.qml";
            }
            PropertyChanges {
                target: catsorterbutton
                buttonState: CatSorterButton.UpdatepagetextButton
            }
        },
        State {
            name: "previousskitpagebutton"
            PropertyChanges {
                target: sorterbutton
                source: "qrc:/GrayCatQtQuick/Qml/CatModule/CatSorter/SkitPageButton.qml";
            }
            PropertyChanges {
                target: catsorterbutton
                buttonState: CatSorterButton.PreviousSkitpageButton
            }
        },
        State {
            name: "nextskitpagebutton"
            PropertyChanges {
                target: sorterbutton
                source: "qrc:/GrayCatQtQuick/Qml/CatModule/CatSorter/SkitPageButton.qml";
            }
            PropertyChanges {
                target: catsorterbutton
                buttonState: CatSorterButton.NextSkitpageButton
            }
        }
    ]

}
