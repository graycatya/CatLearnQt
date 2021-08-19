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

    property int itemSize: 0
    property int spacing: 0
    property int showItemSize: 0
    property int showSpacing: 0
    property int textButtonNumber: 0
    property int buttonPage: 0

    property bool selectState: false

    enum State {
        PreviousButton,
        NextButton,
        UpdatepagetextButton,
        PreviousSkitpageButton,
        NextSkitpageButton
    }

    property int buttonState: CatSorterButton.PreviousButton


    width: showItemSize + showSpacing
    height: showItemSize

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

    function connectsignal()
    {
        catsorter.updateCurrentPage.connect(updatepage);
    }

    function disconnectsignal()
    {
        catsorter.updateCurrentPage.disconnect(updatepage);
    }

    onPreviousPage: {
        if(catsorter.currentPage > 1)
        {
            catsorter.currentPage--;
        }
        updatepage(catsorter.currentPage)
    }

    onNextPage: {
        if(catsorter.currentPage < catsorter.totalPage)
        {
            catsorter.currentPage++;
        }
        updatepage(catsorter.currentPage)
    }

    onTextButtonNumberChanged: {
        if(catsorterbutton.buttonState === CatSorterButton.UpdatepagetextButton)
        {
            if(sorterbutton.visible)
            {
                sorterbutton.item.updateButtonText();
            }
        }
    }

    onUpdatePage: {
        catsorter.currentPage = page;
    }

    function updatepage(page)
    {
        if(sorterbutton.visible)
        {
            if(catsorterbutton.buttonState === CatSorterButton.PreviousButton)
            {
                if(page <= 1)
                {
                    sorterbutton.item.invalid = true
                } else {
                    sorterbutton.item.invalid = false
                }
            } else if(catsorterbutton.buttonState === CatSorterButton.NextButton)
            {
                if(page >= catsorter.totalPage)
                {
                    sorterbutton.item.invalid = true
                } else {
                    sorterbutton.item.invalid = false
                }
            } else if(catsorterbutton.buttonState === CatSorterButton.PreviousSkitpageButton)
            {
                if( (catsorter.currentPage - 1) > 3)
                {
                    catsorterbutton.width = showItemSize + showSpacing
                } else {
                    catsorterbutton.width = 0
                }
            } else if(catsorterbutton.buttonState === CatSorterButton.NextSkitpageButton)
            {
                if( (catsorter.totalPage - catsorter.currentPage) > 3)
                {
                    catsorterbutton.width = showItemSize + showSpacing
                } else {
                    catsorterbutton.width = 0
                }
            }

            if(catsorterbutton.buttonState === CatSorterButton.UpdatepagetextButton)
            {
                if(sorterbutton.visible)
                {
                    sorterbutton.item.updateButtonText();
                }
            } else if(catsorterbutton.buttonState === CatSorterButton.PreviousSkitpageButton
                      || catsorterbutton.buttonState === CatSorterButton.NextSkitpageButton)
            {
                if(sorterbutton.visible)
                {
                    sorterbutton.item.updateButton();
                }
            }
        }
    }

}

