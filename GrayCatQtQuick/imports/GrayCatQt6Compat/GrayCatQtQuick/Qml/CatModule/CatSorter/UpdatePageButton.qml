import QtQuick 2.12
import "../../CatButton"

CatButtonImage {
    id: updatePageButton

    property bool invalid: false

    imagebackground.radius: {
        if(!updatePageButton.enabled || updatePageButton.invalid) {
            return catsorter.buttonRadius_invalid
        } else if(updatePageButton.pressed)
        {
            return catsorter.buttonRadius_pressed
        } else if(updatePageButton.hovered)
        {
            return catsorter.buttonRadius_hovered
        } else if (updatePageButton.checked)
        {
            return catsorter.buttonRadius_pressed
        } else {
            return catsorter.buttonRadius
        }
    }

    imagebackground.color: {
        if(!updatePageButton.enabled || updatePageButton.invalid) {
            return catsorter.buttonBackgroundColor_invalid
        } else if(updatePageButton.pressed)
        {
            return catsorter.buttonBackgroundColor_pressed
        } else if(updatePageButton.hovered)
        {
            return catsorter.buttonBackgroundColor_hovered
        } else if (updatePageButton.checked)
        {
            return catsorter.buttonBackgroundColor_pressed
        } else {
            return catsorter.buttonBackgroundColor
        }
    }

    imagebackground.border.color: {
        if(!updatePageButton.enabled || updatePageButton.invalid) {
            return catsorter.buttonBackgroundBorderColor_invalid
        } else if(updatePageButton.pressed)
        {
            return catsorter.buttonBackgroundBorderColor_pressed
        } else if(updatePageButton.hovered)
        {
            return catsorter.buttonBackgroundBorderColor_hovered
        } else if (updatePageButton.checked)
        {
            return catsorter.buttonBackgroundBorderColor_pressed
        } else {
            return catsorter.buttonBackgroundBorderColor
        }
    }

    imagebackground.border.width: {
        if(!updatePageButton.enabled || updatePageButton.invalid) {
            return catsorter.buttonBackgroundBorderWidth_invalid
        } else if(updatePageButton.pressed)
        {
            return catsorter.buttonBackgroundBorderWidth_pressed
        } else if(updatePageButton.hovered)
        {
            return catsorter.buttonBackgroundBorderWidth_hovered
        } else if (updatePageButton.checked)
        {
            return catsorter.buttonBackgroundBorderWidth_pressed
        } else {
            return catsorter.buttonBackgroundBorderWidth
        }
    }

    btnImgUrl: {
        if(catsorterbutton.buttonState === CatSorterButton.PreviousButton)
        {
            if(!updatePageButton.enabled || updatePageButton.invalid) {
                return catsorter.previousPageButtonImg_invalid;
            } else if(updatePageButton.pressed)
            {
                return catsorter.previousPageButtonImg_pressed
            } else if(updatePageButton.hovered)
            {
                return catsorter.previousPageButtonImg_hovered
            } else if (updatePageButton.checked)
            {
                return catsorter.previousPageButtonImg_pressed
            } else {
                return catsorter.previousPageButtonImg
            }
        } else if(catsorterbutton.buttonState === CatSorterButton.NextButton)
        {
            if(!updatePageButton.enabled || updatePageButton.invalid) {
                return catsorter.nextPageButtonImg_invalid;
            } else if(updatePageButton.pressed)
            {
                return catsorter.nextPageButtonImg_pressed
            } else if(updatePageButton.hovered)
            {
                return catsorter.nextPageButtonImg_hovered
            } else if (updatePageButton.checked)
            {
                return catsorter.nextPageButtonImg_pressed
            } else {
                return catsorter.nextPageButtonImg
            }
        } else {
            return "";
        }
    }

    onInvalidChanged: {
        if(invalid)
        {
            buttonMouse.enabled = false
        } else {
            buttonMouse.enabled = true
        }
    }

    onClicked: {
        if(!invalid)
        {
            if(catsorterbutton.buttonState === CatSorterButton.PreviousButton)
            {
                catsorterbutton.previousPage()
            } else if(catsorterbutton.buttonState === CatSorterButton.NextButton) {
                catsorterbutton.nextPage()
            }
        }
    }

    Component.onCompleted: {
        if(catsorterbutton.buttonState === CatSorterButton.NextButton)
        {
            //console.log("CatSorterButton.NextButton: " + catsorter.currentPage)
            catsorter.updateCurrentPage(catsorter.currentPage);
        }
    }
}
