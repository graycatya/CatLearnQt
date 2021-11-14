import QtQuick 2.12
import QtGraphicalEffects 1.12
import GrayCatQtQuick 1.0
import "../"

Item {
    id: root
    width: 80
    height: 30
    property int languageNumber: -1
    property string languageStr: ""
    property bool selectState: false
    CatButton {
        id: languagebutton
        anchors.fill: parent
        background: Rectangle {
            id: buttonbackground
            anchors.fill: parent
            radius: 5

            color: ProjectObject.languageBackgroundColor
            border.width: selectState ? 1 : 0
            border.color: ProjectObject.styleRectBorderColor

            CatBasicsText {
                anchors.fill: parent
                font.family: ProjectObject.fontFamily
                font.pixelSize: 14
                color: ProjectObject.defaultTextColor
                text: languageStr
            }
        }

        onClicked: {
            if(catconfig != undefined)
            {
                catconfig.setCurrentLanguage(languageStr);
            }
        }
    }

    DropShadow {
        anchors.fill: parent
        horizontalOffset: 0
        verticalOffset: 0
        radius: 8.0
        samples: 18
        color: ProjectObject.catPopupdropshadowColor
        source: buttonbackground
    }

    onLanguageStrChanged: {
        if(catconfig != undefined)
        {
            updateLanguage()
        }
    }

    function updateLanguage()
    {
        let language = catconfig.getCurrentLanguage()
        if(language === languageStr)
        {
            selectState = true
        } else {
            selectState = false
        }
    }

    Component.onCompleted: {
        if(catconfig != undefined)
        {
            catconfig.updateLanguage.connect(function(){
                updateLanguage()
            });
        }
    }
}
