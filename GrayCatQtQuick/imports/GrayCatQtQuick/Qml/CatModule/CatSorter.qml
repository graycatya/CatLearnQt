//qrc:/GrayCatQtQuick/Qml/CatModule/CatSorter/CatSorterButton.qml
import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12
import QtQml.Models 2.12

Item {
    id: catsorter

    property int totalData: 0
    readonly property int totalPage: sorterProperty.totalPage
    property int currentPage: 1
    property int pageButtonCount: 7
    property int pageDataSize: 1

    property int itemSpacing: 10
    property int itemSize: 40

    property bool inputPageState: false

    property string previousPageButtonImg
    property string previousPageButtonImg_hovered
    property string previousPageButtonImg_pressed
    property string previousPageButtonImg_invalid

    property string nextPageButtonImg
    property string nextPageButtonImg_hovered
    property string nextPageButtonImg_pressed
    property string nextPageButtonImg_invalid

    property string previousSkitPageButtonImg
    property string previousSkitPageButtonImg_hovered
    property string previousSkitPageButtonImg_pressed
    property string previousSkitPageButtonImg_invalid

    property string nextSkitPageButtonImg
    property string nextSkitPageButtonImg_hovered
    property string nextSkitPageButtonImg_pressed
    property string nextSkitPageButtonImg_invalid

    property color buttonSkitBackgroundColor: "#01000000"
    property color buttonSkitBackgroundColor_hovered: "#01000000"
    property color buttonSkitBackgroundColor_pressed: "#01000000"
    property color buttonSkitBackgroundColor_invalid: "#01000000"

    property int buttonSkitBackgroundBorderWidth: 0
    property int buttonSkitBackgroundBorderWidth_hovered: 0
    property int buttonSkitBackgroundBorderWidth_pressed: 0
    property int buttonSkitBackgroundBorderWidth_invalid: 0

    property color buttonSkitBackgroundBorderColor: "#01000000"
    property color buttonSkitBackgroundBorderColor_hovered: "#01000000"
    property color buttonSkitBackgroundBorderColor_pressed: "#01000000"
    property color buttonSkitBackgroundBorderColor_invalid: "#01000000"

    property color buttonBackgroundColor: "#01000000"
    property color buttonBackgroundColor_hovered: "#01000000"
    property color buttonBackgroundColor_pressed: "#01000000"
    property color buttonBackgroundColor_invalid: "#01000000"

    property int buttonBackgroundBorderWidth: 0
    property int buttonBackgroundBorderWidth_hovered: 0
    property int buttonBackgroundBorderWidth_pressed: 0
    property int buttonBackgroundBorderWidth_invalid: 0

    property color buttonBackgroundBorderColor: "#01000000"
    property color buttonBackgroundBorderColor_hovered: "#01000000"
    property color buttonBackgroundBorderColor_pressed: "#01000000"
    property color buttonBackgroundBorderColor_invalid: "#01000000"

    property color buttonTextBackgroundColor: "#01000000"
    property color buttonTextBackgroundColor_hovered: "#01000000"
    property color buttonTextBackgroundColor_pressed: "#01000000"
    property color buttonTextBackgroundColor_invalid: "#01000000"
    property color buttonTextBackgroundColor_select: "#01000000"

    property int buttonTextBackgroundBorderWidth: 0
    property int buttonTextBackgroundBorderWidth_hovered: 0
    property int buttonTextBackgroundBorderWidth_pressed: 0
    property int buttonTextBackgroundBorderWidth_invalid: 0
    property int buttonTextBackgroundBorderWidth_select: 0

    property color buttonTextBackgroundBorderColor: "#01000000"
    property color buttonTextBackgroundBorderColor_hovered: "#01000000"
    property color buttonTextBackgroundBorderColor_pressed: "#01000000"
    property color buttonTextBackgroundBorderColor_invalid: "#01000000"
    property color buttonTextBackgroundBorderColor_select: "#01000000"

    property int buttonRadius: 0
    property int buttonRadius_hovered: 0
    property int buttonRadius_pressed: 0
    property int buttonRadius_invalid: 0
    property int buttonRadius_select: 0

    property string fontfamily: "Ubuntu"
    property int fontpixelsize: 12

    property color textColor: "#01000000"
    property color textColor_hovered: "#01000000"
    property color textColor_pressed: "#01000000"
    property color textColor_invalid: "#01000000"
    property color textColor_select: "#01000000"

    property int skitPopupBorderWidth: 0
    property int skitPopupRadius: 0
    property color skitPopupTextColor: "#333333"
    property color skitPopupBorderColor: "#01000000"
    property color skitPopupBackgroundColor: "#01000000"

    property alias sorterView: sorterview

    signal updateCurrentPage(int page)

    clip: true

    QtObject {
        id: sorterProperty

        property int totalPage: 0


        function clearPage() {
            while(sortermodel.count > 0)
            {
                sortermodel.get(0).disconnectsignal()
                sortermodel.get(0).destroy(50);
                sortermodel.remove(0);
            }
        }

        function initPages() {
            clearPage();

            sortermodel.clear();
            let buttonNumber = ((catsorter.pageButtonCount%2 == 0) ? catsorter.pageButtonCount + 1 : catsorter.pageButtonCount)  + 4;
            let textbuttonNumber = 1;
            for(let i = 0; i < buttonNumber; i++)
            {
                let item = Qt.createComponent("qrc:/GrayCatQtQuick/Qml/CatModule/CatSorter/CatSorterButton.qml");
                sortermodel.insert(sorterview.model.count, item.createObject(sorterview));
                sortermodel.get(sorterview.model.count - 1).itemSize = itemSize;
                sortermodel.get(sorterview.model.count - 1).spacing = itemSpacing;
                sortermodel.get(sorterview.model.count - 1).showItemSize = itemSize;
                sortermodel.get(sorterview.model.count - 1).showSpacing = itemSpacing;
                if(i === 0)
                {
                    // left page button
                    sortermodel.get(sorterview.model.count - 1).state = "previousbutton";
                    sortermodel.get(sorterview.model.count - 1).spacing = 0;
                    sortermodel.get(sorterview.model.count - 1).showSpacing = 0;

                } else if(i === buttonNumber - 1)
                {
                    // right page button
                    sortermodel.get(sorterview.model.count - 1).state = "nextbutton";
                } else if(i === 2)
                {
                    // left skit page button
                    sortermodel.get(sorterview.model.count - 1).state = "previousskitpagebutton";
                } else if(i === buttonNumber - 3)
                {
                    // right skit page button
                    sortermodel.get(sorterview.model.count - 1).state = "nextskitpagebutton";
                } else {
                    sortermodel.get(sorterview.model.count - 1).state = "updatepagetextbutton";
                    sortermodel.get(sorterview.model.count - 1).textButtonNumber = textbuttonNumber;
                    textbuttonNumber++;
                }
                sortermodel.get(sorterview.model.count - 1).connectsignal()
                sortermodel.get(sorterview.model.count - 1).updatepage(currentPage)
                sorterview.positionViewAtEnd();
            }

            sorterview.positionViewAtBeginning();
        }
    }

    ObjectModel {
        id: sortermodel
    }

    ListView {
        id: sorterview
        anchors.fill: parent

        orientation: ListView.Horizontal
        interactive: false

        model: sortermodel

        clip: true
        spacing: 0

    }

    onTotalDataChanged: {
        sorterProperty.totalPage = totalData / pageDataSize + ((totalData%pageDataSize != 0) ? 1 : 0);
        sorterProperty.initPages();
    }

    onPageButtonCountChanged: {
        if(pageButtonCount < 7)
        {
            pageButtonCount = 7;
            sorterProperty.initPages();
        } else {
            sorterProperty.initPages();
        }
    }



    onPageDataSizeChanged: {
        if(pageDataSize < 1)
        {
            pageDataSize = 1;
            sorterProperty.totalPage = totalData / pageDataSize + ((totalData%pageDataSize != 0) ? 1 : 0);
            sorterProperty.initPages();
        } else {
            sorterProperty.totalPage = totalData / pageDataSize + ((totalData%pageDataSize != 0) ? 1 : 0);
            sorterProperty.initPages();
        }
    }

    onItemSizeChanged: {
        sorterProperty.initPages();
    }

    onItemSpacingChanged: {
        sorterProperty.initPages();
    }

    onCurrentPageChanged: {
        updateCurrentPage(currentPage);
    }

    onTotalPageChanged: {
        if(currentPage >= totalPage)
        {
            currentPage = totalPage;
            updateCurrentPage(currentPage);
        }
    }

    Component.onCompleted: {
        timer.start();
    }

    Timer {
        id: timer
        interval: 300
        onTriggered: {
            updateCurrentPage(currentPage);
        }
    }

}

