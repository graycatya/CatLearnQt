import QtQuick 2.12
import "../../CatButton"

CatButton {
    id: updatepagetextbutton

    background: Rectangle {
        radius: {
            if(!catsorterbutton.selectState)
            {
                if(!updatepagetextbutton.enabled || updatepagetextbutton.invalid) {
                    return catsorter.buttonRadius_invalid
                } else if(updatepagetextbutton.pressed)
                {
                    return catsorter.buttonRadius_pressed
                } else if(updatepagetextbutton.hovered)
                {
                    return catsorter.buttonRadius_hovered
                } else if (updatepagetextbutton.checked)
                {
                    return catsorter.buttonRadius_pressed
                } else {
                    return catsorter.buttonRadius
                }
            } else {
                return catsorter.buttonRadius_select
            }
        }

        color: {
            if(!catsorterbutton.selectState)
            {
                if(!updatepagetextbutton.enabled || updatepagetextbutton.invalid) {
                    return catsorter.buttonTextBackgroundColor_invalid
                } else if(updatepagetextbutton.pressed)
                {
                    return catsorter.buttonTextBackgroundColor_pressed
                } else if(updatepagetextbutton.hovered)
                {
                    return catsorter.buttonTextBackgroundColor_hovered
                } else if (updatepagetextbutton.checked)
                {
                    return catsorter.buttonTextBackgroundColor_pressed
                } else {
                    return catsorter.buttonTextBackgroundColor
                }
            } else {
                return catsorter.buttonTextBackgroundColor_select
            }
        }

        border.width: {
            if(!catsorterbutton.selectState)
            {
                if(!updatepagetextbutton.enabled || updatepagetextbutton.invalid) {
                    return catsorter.buttonTextBackgroundBorderWidth_invalid
                } else if(updatepagetextbutton.pressed)
                {
                    return catsorter.buttonTextBackgroundBorderWidth_pressed
                } else if(updatepagetextbutton.hovered)
                {
                    return catsorter.buttonTextBackgroundBorderWidth_hovered
                } else if (updatepagetextbutton.checked)
                {
                    return catsorter.buttonTextBackgroundBorderWidth_pressed
                } else {
                    return catsorter.buttonTextBackgroundBorderWidth
                }
            } else {
                return catsorter.buttonTextBackgroundBorderWidth_select
            }
        }

        border.color: {
            if(!catsorterbutton.selectState)
            {
                if(!updatepagetextbutton.enabled || updatepagetextbutton.invalid) {
                    return catsorter.buttonTextBackgroundBorderColor_invalid
                } else if(updatepagetextbutton.pressed)
                {
                    return catsorter.buttonTextBackgroundBorderColor_pressed
                } else if(updatepagetextbutton.hovered)
                {
                    return catsorter.buttonTextBackgroundBorderColor_hovered
                } else if (updatepagetextbutton.checked)
                {
                    return catsorter.buttonTextBackgroundBorderColor_pressed
                } else {
                    return catsorter.buttonTextBackgroundBorderColor
                }
            } else {
                return catsorter.buttonTextBackgroundBorderColor_select
            }
        }

        Text {
            id: pageText
            anchors.fill: parent
            font.family: catsorter.fontfamily
            font.pixelSize: catsorter.fontpixelsize
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: {
                if(!catsorterbutton.selectState)
                {
                    if(!updatepagetextbutton.enabled || updatepagetextbutton.invalid) {
                        return catsorter.textColor_invalid
                    } else if(updatepagetextbutton.pressed)
                    {
                        return catsorter.textColor_pressed
                    } else if(updatepagetextbutton.hovered)
                    {
                        return catsorter.textColor_hovered
                    } else if (updatepagetextbutton.checked)
                    {
                        return catsorter.textColor_pressed
                    } else {
                        return catsorter.textColor
                    }
                } else {
                    return catsorter.textColor_select
                }
            }

        }
    }

    function updateButtonText()
    {
        if(catsorter.totalPage >= catsorter.pageButtonCount)
        {
            if(catsorterbutton.textButtonNumber === 1)
            {
                pageText.text = 1
                buttonPage = 1
                updateButtonState()
                updateButtonWidth()
                return;
            } else if(catsorterbutton.textButtonNumber ===
                      ((catsorter.pageButtonCount % 2 == 0) ?
                           catsorter.pageButtonCount + 1 :
                           catsorter.pageButtonCount))
            {
                pageText.text = catsorter.totalPage
                buttonPage = catsorter.totalPage
                updateButtonState()
                updateButtonWidth()
                return;
            }

            if(catsorter.currentPage - 1 > 3
                    && (catsorter.totalPage - catsorter.currentPage) > 3)
            {
                if(catsorterbutton.textButtonNumber !== 1
                        && catsorterbutton.textButtonNumber
                        !== (catsorter.pageButtonCount % 2 == 0)
                        ? catsorter.pageButtonCount + 1
                        : catsorter.pageButtonCount)
                {
                    page = catsorterbutton.textButtonNumber -
                            (catsorter.pageButtonCount + ((catsorter.pageButtonCount % 2 == 0) ? 1 : 0))/2 + catsorter.currentPage;

                    pageText.text = page
                    buttonPage = page
                }
            } else if( catsorter.currentPage - 1 > 3 )
            {
                if(catsorterbutton.textButtonNumber !== 1
                        && catsorterbutton.textButtonNumber
                        !== (catsorter.pageButtonCount % 2 == 0)
                        ? catsorter.pageButtonCount + 1
                        : catsorter.pageButtonCount)
                {
                    // 奇偶判断
                    if(catsorter.pageButtonCount % 2 == 0)
                    {
                        pageText.text = catsorter.totalPage -
                                (catsorter.pageButtonCount - (catsorterbutton.textButtonNumber))
                        buttonPage = catsorter.totalPage -
                                (catsorter.pageButtonCount - (catsorterbutton.textButtonNumber))
                    } else {
                        pageText.text = catsorter.totalPage -
                                (catsorter.pageButtonCount - catsorterbutton.textButtonNumber)
                        buttonPage = catsorter.totalPage -
                                (catsorter.pageButtonCount - catsorterbutton.textButtonNumber)
                    }
                }
            } else if( (catsorter.totalPage - catsorter.currentPage) > 3 )
            {
                if(catsorterbutton.textButtonNumber !== 1
                        && catsorterbutton.textButtonNumber
                        !== (catsorter.pageButtonCount % 2 == 0)
                        ? catsorter.pageButtonCount + 1
                        : catsorter.pageButtonCount)
                {
                    pageText.text = catsorterbutton.textButtonNumber
                    buttonPage = catsorterbutton.textButtonNumber
                }
            }

            updateButtonState()
            updateButtonWidth()
        } else {
            pageText.text = catsorterbutton.textButtonNumber
            buttonPage = catsorterbutton.textButtonNumber
            updateButtonState()
            updateButtonWidth()
        }
    }

    function updateButtonState()
    {
        if(buttonPage === catsorter.currentPage)
        {
            catsorterbutton.selectState = true
        } else {
            catsorterbutton.selectState = false
        }
    }

    function updateButtonWidth()
    {
        if(catsorterbutton.textButtonNumber !== 1
                && catsorterbutton.textButtonNumber
                !== (catsorter.pageButtonCount % 2 == 0)
                ? catsorter.pageButtonCount + 1
                : catsorter.pageButtonCount)
        {
            if(catsorter.currentPage - 1 > 3
                    && (catsorter.totalPage - catsorter.currentPage) > 3)
            {
                if(catsorter.pageButtonCount % 2 == 0)
                {
                    if(catsorterbutton.textButtonNumber === catsorter.pageButtonCount)
                    {
                        catsorterbutton.visible = true
                    }
                }
            } else {
                if(catsorter.pageButtonCount % 2 == 0)
                {
                    if(catsorterbutton.textButtonNumber === catsorter.pageButtonCount)
                    {
                        catsorterbutton.visible = false
                        catsorterbutton.width = 0
                    }
                }
            }
        }

        if(catsorterbutton.textButtonNumber > catsorter.totalPage)
        {
            catsorterbutton.visible = false
            catsorterbutton.width = 0
        }

        if(catsorterbutton.visible)
        {
            if((pageText.contentWidth + 10) > catsorterbutton.itemSize)
            {
                catsorterbutton.width = pageText.contentWidth + 10 + catsorterbutton.showSpacing
            } else {
                catsorterbutton.width = catsorterbutton.showItemSize + catsorterbutton.showSpacing
            }
        }

    }

    onClicked: {
        if(!catsorterbutton.selectState)
        {
            catsorterbutton.updatePage(catsorterbutton.buttonPage)
        }
    }

}
