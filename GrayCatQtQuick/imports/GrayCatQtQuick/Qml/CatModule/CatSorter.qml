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

    property string previousPageButtonImg
    property string previousPageButtonImg_Hovered
    property string previousPageButtonImg_Pressed
    property string previousPageButtonImg_invalid

    property string nextPageButtonImg
    property string nextPageButtonImg_Hovered
    property string nextPageButtonImg_Pressed
    property string nextPageButtonImg_invalid

    property color buttonBackgroundColor
    property color buttonBackgroundColor_hovered
    property color buttonBackgroundColor_pressed
    property color buttonBackgroundColor_invalid

    property int buttonBackgroundBorderWidth: 0
    property int buttonBackgroundBorderWidth_hovered: 0
    property int buttonBackgroundBorderWidth_pressed: 0
    property int buttonBackgroundBorderWidth_Invalid: 0

    property color buttonBackgroundBorderColor
    property color buttonBackgroundBorderColor_hovered
    property color buttonBackgroundBorderColor_pressed
    property color buttonBackgroundBorderColor_invalid

    property int buttonRadius: 0


    clip: true

    QtObject {
        id: sorterProperty

        property int totalPage: 0


        function clearPage() {
            while(sortermodel.count > 0)
            {
                //sortermodel.get(0).disconnectupdateState()
                sortermodel.get(0).destroy(50);
                sortermodel.remove(0);
            }
        }

        function initPages() {
            clearPage();

            sortermodel.clear();
            let buttonNumber = catsorter.totalPage + 4;
            for(let i = 0; i < buttonNumber; i++)
            {
                let item = Qt.createComponent("qrc:/GrayCatQtQuick/Qml/CatModule/CatSorter/CatSorterButton.qml");
                sortermodel.insert(sorterview.model.count, item.createObject(sorterview));

                if(i === 0)
                {
                    // left page button
                    sortermodel.get(sorterview.model.count - 1).state = "previousbutton";

                } else if(i === buttonNumber-1)
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
                    if(i === 1)
                    {

                    } else if(i === buttonNumber - 2)
                    {

                    }
                }


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
        //width: contentWidth

        orientation: ListView.Horizontal

        model: sortermodel

        clip: true
        spacing: 0

    }

    onTotalDataChanged: {
        sorterProperty.totalPage = totalData / pageDataSize;
        sorterProperty.initPages();
    }

    onPageButtonCountChanged: {
        if(pageButtonCount < 5)
        {
            pageButtonCount = 5;
            sorterProperty.initPages();
        } else {
            sorterProperty.initPages();
        }
    }



    onPageDataSizeChanged: {
        if(pageDataSize < 1)
        {
            pageDataSize = 1;
            sorterProperty.initPages();
        } else {
            sorterProperty.totalPage = totalData / pageDataSize;
            sorterProperty.initPages();
        }
    }

    onItemSizeChanged: {
        sorterProperty.initPages();
    }

    onItemSpacingChanged: {
        sorterProperty.initPages();
    }
}
