import QtQuick 2.12
import GrayCatQtQuick 1.0
import QtQuick.Layouts 1.12
import "../"

Rectangle {
    id: root
    //id: demoimageflipable
    color: "transparent"

    ColumnLayout {
        id: columnlayout
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10
        RowLayout {
            Layout.preferredHeight: 32
            Layout.maximumHeight: 32
            Layout.fillWidth: true

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            CatSorter {
                id: sorter0
                Layout.preferredHeight: 32
                Layout.preferredWidth: sorterView.contentWidth
                totalData: 10000
                pageDataSize: 10
                pageButtonCount: 7
                currentPage: 1

                itemSize: 32
                previousPageButtonImg: ProjectObject.getCurrentResourcePath() + "SorterPreviousButtonDefault.png"
                previousPageButtonImg_hovered: ProjectObject.getCurrentResourcePath() + "SorterPreviousButtonHover.png"
                previousPageButtonImg_pressed: ProjectObject.getCurrentResourcePath() + "SorterPreviousButtonPressed.png"
                previousPageButtonImg_invalid: ProjectObject.getCurrentResourcePath() + "SorterPreviousButtonDefault.png"

                nextPageButtonImg: ProjectObject.getCurrentResourcePath() + "SorterNextButtonDefault.png"
                nextPageButtonImg_hovered: ProjectObject.getCurrentResourcePath() + "SorterNextButtonHove.png"
                nextPageButtonImg_pressed: ProjectObject.getCurrentResourcePath() + "SorterNextButtonPressed.png"
                nextPageButtonImg_invalid: ProjectObject.getCurrentResourcePath() + "SorterNextButtonDefault.png"

                buttonBackgroundColor: "#01000000"
                buttonBackgroundColor_hovered: "#01000000"
                buttonBackgroundColor_pressed: "#01000000"
                buttonBackgroundColor_invalid: "#01000000"

                buttonTextBackgroundColor: "#01000000"
                buttonTextBackgroundColor_hovered: "#4C4C4C"
                buttonTextBackgroundColor_pressed: "#4C4C4C"
                buttonTextBackgroundColor_invalid: "#01000000"
                buttonTextBackgroundColor_select: "#3C3C3C"

                buttonBackgroundBorderColor: "#01000000"
                buttonBackgroundBorderColor_hovered: "#01000000"
                buttonBackgroundBorderColor_pressed: "#01000000"
                buttonBackgroundBorderColor_invalid: "#01000000"

                buttonBackgroundBorderWidth: 0
                buttonBackgroundBorderWidth_hovered: 0
                buttonBackgroundBorderWidth_pressed: 0
                buttonBackgroundBorderWidth_invalid: 0

                previousSkitPageButtonImg: ProjectObject.getCurrentResourcePath() + "SorterSkitNextButtonDefault.png"
                previousSkitPageButtonImg_hovered: ProjectObject.getCurrentResourcePath() + "SorterPreviousButtonHover.png"
                previousSkitPageButtonImg_pressed: ProjectObject.getCurrentResourcePath() + "SorterPreviousButtonHover.png"
                previousSkitPageButtonImg_invalid: ProjectObject.getCurrentResourcePath() + "SorterSkitNextButtonDefault.png"

                nextSkitPageButtonImg: ProjectObject.getCurrentResourcePath() + "SorterSkitNextButtonDefault.png"
                nextSkitPageButtonImg_hovered: ProjectObject.getCurrentResourcePath() + "SorterNextButtonHove.png"
                nextSkitPageButtonImg_pressed: ProjectObject.getCurrentResourcePath() + "SorterNextButtonHove.png"
                nextSkitPageButtonImg_invalid: ProjectObject.getCurrentResourcePath() + "SorterSkitNextButtonDefault.png"

                buttonRadius: 5
                buttonRadius_hovered: 5
                buttonRadius_pressed: 5
                buttonRadius_invalid: 5
                buttonRadius_select: 5

                fontfamily: ProjectObject.fontFamily
                textColor: "#FFFFFF"
                textColor_hovered: "#FFFFFF"
                textColor_pressed: "#FFFFFF"
                textColor_select: "#FFFFFF"
    /*
                       skitPopupBorderWidth: 1
                       skitPopupRadius: 5
                       skitPopupTextColor: "#333333"
                       skitPopupBorderColor: "#3399FF"
                       skitPopupBackgroundColor: "#FFFFFF"
                       */


                onUpdateCurrentPage: {
                    console.log("update currentpage: " + page)
                }

            }

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

        }

        RowLayout {
            Layout.preferredHeight: 32
            Layout.maximumHeight: 32
            Layout.fillWidth: true

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            CatSorter {
                id: sorter1
                Layout.preferredHeight: 32
                Layout.preferredWidth: sorterView.contentWidth
                totalData: 10000
                pageDataSize: 10
                pageButtonCount: 7
                currentPage: 1

                itemSize: 32
                previousPageButtonImg: ProjectObject.getCurrentResourcePath() + "SorterPreviousButtonDefault.png"
                previousPageButtonImg_hovered: ProjectObject.getCurrentResourcePath() + "SorterPreviousButtonHover.png"
                previousPageButtonImg_pressed: ProjectObject.getCurrentResourcePath() + "SorterPreviousButtonPressed.png"
                previousPageButtonImg_invalid: ProjectObject.getCurrentResourcePath() + "SorterPreviousButtonDefault.png"

                nextPageButtonImg: ProjectObject.getCurrentResourcePath() + "SorterNextButtonDefault.png"
                nextPageButtonImg_hovered: ProjectObject.getCurrentResourcePath() + "SorterNextButtonHove.png"
                nextPageButtonImg_pressed: ProjectObject.getCurrentResourcePath() + "SorterNextButtonPressed.png"
                nextPageButtonImg_invalid: ProjectObject.getCurrentResourcePath() + "SorterNextButtonDefault.png"

                buttonBackgroundColor: "#01000000"
                buttonBackgroundColor_hovered: "#01000000"
                buttonBackgroundColor_pressed: "#01000000"
                buttonBackgroundColor_invalid: "#01000000"

                buttonTextBackgroundColor: "#01000000"
                buttonTextBackgroundColor_hovered: "#4C4C4C"
                buttonTextBackgroundColor_pressed: "#4C4C4C"
                buttonTextBackgroundColor_invalid: "#01000000"
                buttonTextBackgroundColor_select: "#3C3C3C"

                buttonBackgroundBorderColor: "#01000000"
                buttonBackgroundBorderColor_hovered: "#01000000"
                buttonBackgroundBorderColor_pressed: "#01000000"
                buttonBackgroundBorderColor_invalid: "#01000000"

                buttonBackgroundBorderWidth: 0
                buttonBackgroundBorderWidth_hovered: 0
                buttonBackgroundBorderWidth_pressed: 0
                buttonBackgroundBorderWidth_invalid: 0

                previousSkitPageButtonImg: ProjectObject.getCurrentResourcePath() + "SorterSkitNextButtonDefault.png"
                previousSkitPageButtonImg_hovered: ProjectObject.getCurrentResourcePath() + "SorterPreviousButtonHover.png"
                previousSkitPageButtonImg_pressed: ProjectObject.getCurrentResourcePath() + "SorterPreviousButtonHover.png"
                previousSkitPageButtonImg_invalid: ProjectObject.getCurrentResourcePath() + "SorterSkitNextButtonDefault.png"

                nextSkitPageButtonImg: ProjectObject.getCurrentResourcePath() + "SorterSkitNextButtonDefault.png"
                nextSkitPageButtonImg_hovered: ProjectObject.getCurrentResourcePath() + "SorterNextButtonHove.png"
                nextSkitPageButtonImg_pressed: ProjectObject.getCurrentResourcePath() + "SorterNextButtonHove.png"
                nextSkitPageButtonImg_invalid: ProjectObject.getCurrentResourcePath() + "SorterSkitNextButtonDefault.png"

                buttonRadius: 5
                buttonRadius_hovered: 5
                buttonRadius_pressed: 5
                buttonRadius_invalid: 5
                buttonRadius_select: 5

                fontfamily: ProjectObject.fontFamily
                textColor: "#FFFFFF"
                textColor_hovered: "#FFFFFF"
                textColor_pressed: "#FFFFFF"
                textColor_select: "#FFFFFF"

                skitPopupBorderWidth: 0
                skitPopupRadius: 5
                skitPopupTextColor: "#FFFFFF"
                skitPopupBorderColor: "#2C2C2C"
                skitPopupBackgroundColor: "#3C3C3C"

                inputPageState: true

                onUpdateCurrentPage: {
                    console.log("update currentpage: " + page)
                }

            }
            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

    }
/*
        CatSorter {
            Layout.preferredHeight: 40
            Layout.preferredWidth: sorterView.contentWidth
            totalData: 1000
            pageDataSize: 100
        }

        CatSorter {
            Layout.preferredHeight: 40
            Layout.preferredWidth: sorterView.contentWidth
            totalData: 1000
            pageDataSize: 100
        }

*/

}
