import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import "../../CatButton"

Item {
    id: skitpagebutton

    property bool inputPageState: catsorter.inputPageState

    CatButton {
        id: skitbutton
        anchors.fill: parent

        background: Rectangle {
            anchors.fill: parent
            radius: {
                if(!skitbutton.enabled || skitbutton.invalid) {
                    return catsorter.buttonRadius_invalid
                } else if(skitbutton.pressed)
                {
                    return catsorter.buttonRadius_pressed
                } else if(skitbutton.hovered)
                {
                    return catsorter.buttonRadius_hovered
                } else if (skitbutton.checked)
                {
                    return catsorter.buttonRadius_pressed
                } else {
                    return catsorter.buttonRadius
                }
            }

            color: {
                if(!skitbutton.enabled || skitbutton.invalid) {
                    return catsorter.buttonSkitBackgroundColor_invalid
                } else if(skitbutton.pressed)
                {
                    return catsorter.buttonSkitBackgroundColor_pressed
                } else if(skitbutton.hovered)
                {
                    return catsorter.buttonSkitBackgroundColor_hovered
                } else if (skitbutton.checked)
                {
                    return catsorter.buttonSkitBackgroundColor_pressed
                } else {
                    return catsorter.buttonSkitBackgroundColor
                }
            }

            border.color: {
                if(!skitbutton.enabled || skitbutton.invalid) {
                    return catsorter.buttonSkitBackgroundBorderColor_invalid
                } else if(skitbutton.pressed)
                {
                    return catsorter.buttonSkitBackgroundBorderColor_pressed
                } else if(skitbutton.hovered)
                {
                    return catsorter.buttonSkitBackgroundBorderColor_hovered
                } else if (skitbutton.checked)
                {
                    return catsorter.buttonSkitBackgroundBorderColor_pressed
                } else {
                    return catsorter.buttonSkitBackgroundBorderColor
                }
            }

            border.width: {
                if(!skitbutton.enabled || skitbutton.invalid) {
                    return catsorter.buttonSkitBackgroundBorderWidth_invalid
                } else if(skitbutton.pressed)
                {
                    return catsorter.buttonSkitBackgroundBorderWidth_pressed
                } else if(skitbutton.hovered)
                {
                    return catsorter.buttonSkitBackgroundBorderWidth_hovered
                } else if (skitbutton.checked)
                {
                    return catsorter.buttonSkitBackgroundBorderWidth_pressed
                } else {
                    return catsorter.buttonSkitBackgroundBorderWidth
                }
            }

            Image {
                anchors.centerIn: parent
                width: sourceSize.width
                height: sourceSize.height
                source: {
                    if(catsorterbutton.buttonState === CatSorterButton.PreviousSkitpageButton)
                    {
                        if(!skitbutton.enabled || skitbutton.invalid) {
                            return catsorter.previousSkitPageButtonImg_invalid;
                        } else if(skitbutton.pressed)
                        {
                            return catsorter.previousSkitPageButtonImg_pressed
                        } else if(skitbutton.hovered)
                        {
                            return catsorter.previousSkitPageButtonImg_hovered
                        } else if (skitbutton.checked)
                        {
                            return catsorter.previousSkitPageButtonImg_pressed
                        } else {
                            return catsorter.previousSkitPageButtonImg
                        }
                    } else if(catsorterbutton.buttonState === CatSorterButton.NextSkitpageButton)
                    {
                        if(!skitbutton.enabled || skitbutton.invalid) {
                            return catsorter.nextSkitPageButtonImg_invalid;
                        } else if(skitbutton.pressed)
                        {
                            return catsorter.nextSkitPageButtonImg_pressed
                        } else if(skitbutton.hovered)
                        {
                            return catsorter.nextSkitPageButtonImg_hovered
                        } else if (skitbutton.checked)
                        {
                            return catsorter.nextSkitPageButtonImg_pressed
                        } else {
                            return catsorter.nextSkitPageButtonImg
                        }
                    } else {
                        return "";
                    }
                }
            }
        }

        onClicked: {
            if(!catsorter.inputPageState)
            {
                if(catsorterbutton.buttonState === CatSorterButton.PreviousSkitpageButton)
                {
                    catsorterbutton.updatePage(catsorter.currentPage - 4)
                } else if(catsorterbutton.buttonState === CatSorterButton.NextSkitpageButton)
                {
                    catsorterbutton.updatePage(catsorter.currentPage + 4)
                }
            } else {
                popup.visible = true
                pageinput.text = ""
                catsorterbutton.width = catsorterbutton.showItemSize + catsorterbutton.showSpacing
            }
        }

    }

    Popup {
        id: popup
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        focus: true

        background: Rectangle {
            border.width: catsorter.skitPopupBorderWidth

            border.color: catsorter.skitPopupBorderColor

            radius: catsorter.skitPopupRadius

            color: catsorter.skitPopupBackgroundColor

            TextInput {
                id: pageinput
                anchors.fill: parent
                validator:  RegularExpressionValidator { regularExpression: /^\d+$/ }
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: catsorter.skitPopupTextColor
                font.family: catsorter.fontfamily
                font.pixelSize: catsorter.fontpixelsize
                focus: true

                onTextChanged: {
                    if(text != "")
                    {
                        if(Number(text) < 1)
                        {
                            text = 1
                        } else if(Number(text) > catsorter.totalPage)
                        {
                            text = catsorter.totalPage
                        }
                    }
                    if((pageinput.contentWidth + 20) >= catsorterbutton.itemSize)
                    {
                        catsorterbutton.width = pageinput.contentWidth + 20 + catsorterbutton.showSpacing
                    } else {
                        catsorterbutton.width = catsorterbutton.showItemSize + catsorterbutton.showSpacing
                    }
                }
            }

        }

        onVisibleChanged: {
            if(!visible)
            {
                if(pageinput.text != "")
                {
                    catsorterbutton.updatePage(Number(pageinput.text))
                }
                catsorterbutton.width = catsorterbutton.showItemSize + catsorterbutton.showSpacing
            } else {

            }
        }

    }


    function updateButton()
    {
        if(catsorter.totalPage <= catsorter.pageButtonCount)
        {
            catsorterbutton.visible = false
            catsorterbutton.width = 0
        }
    }

}
