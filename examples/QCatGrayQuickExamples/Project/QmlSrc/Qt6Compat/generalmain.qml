import QtQuick
import QtQml
import QtQuick.Controls
import QtQuick.Layouts

//import Qt.labs.calendar
import QtQuick.Window
import QCatGrayQuick
//import CatEncp
import "FunctionLayout"
import "./MoreFunctionViews"

Window {
    id: applicationWindow
    width: 900
    height: 600
    minimumWidth: 900
    minimumHeight: 600
    visible: true


    //color: ProjectObject.appBackgroundColor
    CatMessage {
        id: message
        showCloseButton: true

        succeed_image: ProjectObject.getCurrentResourcePath() + "message_succeed.png"
        warning_image: ProjectObject.getCurrentResourcePath() + "message_warning.png"
        information_image: ProjectObject.getCurrentResourcePath() + "message_info.png"
        errored_image: ProjectObject.getCurrentResourcePath() + "message_error.png"

        close_button_image_Normal: ProjectObject.getCurrentResourcePath() + "message_close.png"
        close_button_image_Hovered: ProjectObject.getCurrentResourcePath() + "message_close.png"
        close_button_image_Pressed: ProjectObject.getCurrentResourcePath() + "message_close.png"
        close_button_image_Disbaled: ProjectObject.getCurrentResourcePath() + "message_close.png"

        succeed_back_color: ProjectObject.message_succeed_back_color
        warning_back_color: ProjectObject.message_warning_back_color
        information_back_color: ProjectObject.message_information_back_color
        errored_back_color: ProjectObject.message_errored_back_color

        succeed_border_color: ProjectObject.message_succeed_border_color
        warning_border_color: ProjectObject.message_warning_border_color
        information_border_color: ProjectObject.message_information_border_color
        errored_border_color: ProjectObject.message_errored_border_color

        message_text_succeed_color: ProjectObject.message_text_succeed_color
        message_text_warning_color: ProjectObject.message_text_warning_color
        message_text_information_color: ProjectObject.message_text_information_color
        message_text_errored_color: ProjectObject.message_text_errored_color

        succeed_border_width: 1
        warning_border_width: 1
        information_border_width: 1
        errored_border_width: 1

        succeed_back_radius: 3
        warning_back_radius: 3
        information_back_radius: 3
        errored_back_radius: 3

        message_font.pixelSize: 16
        message_font.family: ProjectObject.fontFamily

        message_width: 400

        topMargin: 20
        bottomMargin: 20
        rightMargin: 20
        leftMargin: 20

        // layoutDirection: CatMessage.TopRightDirection
        // layoutDirection: CatMessage.TopLeftDirection
        layoutDirection: CatMessage.TopCenterDirection
        // layoutDirection: CatMessage.LeftCenterDirection
        // layoutDirection: CatMessage.RightCenterDirection
        // layoutDirection: CatMessage.BottomCenterDirection
        // layoutDirection: CatMessage.BottomLeftDirection
        // layoutDirection: CatMessage.BottomRightDirection

       Component.onCompleted: {
           ProjectObject.messageObj = message
       }
    }

    ColumnLayout {
        id: rootLayout
        spacing: 0
        anchors.fill: parent

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 40
            Layout.maximumHeight: 40
            Layout.minimumHeight: 40
            GeneralTitleItem {
                id: win10titleitem
                anchors.fill: parent

            }

            CatDropShadow {
                anchors.fill: win10titleitem
                horizontalOffset: 0
                verticalOffset: 0
                radius: 8.0
                samples: 18
                color: ProjectObject.catPopupdropshadowColor
                source: win10titleitem
            }

        }


        Item {
            id: functionRect
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.topMargin: 20
            Layout.leftMargin: 20
            Layout.rightMargin: 20
            Layout.bottomMargin: 20
            //color: ProjectObject.appBackgroundColor

            LayoutView {
                anchors.fill: functionRect
            }

            CatFps {
                id: catfps
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.rightMargin: -15
                anchors.topMargin: -15
                gradient0Color: ProjectObject.fpsgradient0Color
                gradient1Color: ProjectObject.fpsgradient1Color
//                width: 120
//                height: 32
            }
        }

    }

    MoreView {
        id: moreview
        visible: false
    }



    Component.onCompleted: {
        //catLog.debug_print("run ui, system is: " + Qt.platform.os);
        if(catconfig != undefined)
        {
            ProjectObject.currentTheme = catconfig.getValue("Style");
        }
        //var key = CatEncp.md5("123456")

        //var data = CatEncp.aes_256_Cbc_Encrypt("hello world", key);
        //data = CatEncp.aes_256_Cbc_Decrypt(data, key);

        //catLog.debug_print(data);

        if(Qt.platform.os === "osx")
        {
            catfps.anchors.rightMargin = 0
        }

        color = ProjectObject.appBackgroundColor
        ProjectObject.updateCurrentThemeed.connect(function(){
            animation.restart();
        });
        //catLog.debug_print("system font familys: " + catconfig.systemFontFamily())
    }

    PropertyAnimation  {
        id: animation
        target: applicationWindow;
        property: "color";
        from: color
        to: ProjectObject.appBackgroundColor
        duration: ProjectObject.settingtransition ? 400 : 0
    }

}
