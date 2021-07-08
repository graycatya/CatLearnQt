import QtQuick 2.12
import "../CatButton"
import "../CatBasics"

Rectangle {
    id: root
    property color backdropColor: "#2C2C2C"
    property color titleColor: "#4C4C4C"
    implicitWidth: 350
    implicitHeight: 350

    radius: 5

    color: root.backdropColor

    CatRectangle {
        id: functionItem
        anchors.top: root.top
        anchors.left: root.left
        anchors.right: root.right

        implicitHeight: 40

        backdropRadius: root.radius
        leftBottomRound: false
        rightBottomRound: false
        leftTopRound: root.radius === 0 ? false : true
        rightTopRound: root.radius === 0 ? false : true

        backdropColor: root.titleColor

        CatButtonImage {
            id: previousYear
            anchors.verticalCenter: parent
            anchors.left: parent.left
            anchors.leftMargin: 5
            width: 25
            height: 25
            btnImgNormal: "qrc:/GrayCatQtQuick/IconResource/LeftLeftButton_default.svg"
            btnImgHovered: "qrc:/GrayCatQtQuick/IconResource/LeftLeftButton_gray.svg"
            btnImgPressed: "qrc:/GrayCatQtQuick/IconResource/LeftLeftButton_gray.svg"
            btnImgDisbaled: "qrc:/GrayCatQtQuick/IconResource/LeftLeftButton_gray.svg"


        }

        CatButtonImage {
            id: lastMonth
            anchors.verticalCenter: parent
            anchors.left: previousYear.right
            anchors.leftMargin: 0
            width: 25
            height: 25
            btnImgNormal: "qrc:/GrayCatQtQuick/IconResource/LeftButton_default.svg"
            btnImgHovered: "qrc:/GrayCatQtQuick/IconResource/LeftButton_gray.svg"
            btnImgPressed: "qrc:/GrayCatQtQuick/IconResource/LeftButton_gray.svg"
            btnImgDisbaled: "qrc:/GrayCatQtQuick/IconResource/LeftButton_gray.svg"

        }

        CatButtonImage {
            id: nextMonth
            anchors.verticalCenter: parent
            anchors.right: nextYear.left
            anchors.rightMargin: 0
            width: 25
            height: 25
            btnImgNormal: "qrc:/GrayCatQtQuick/IconResource/RightButton_default.svg"
            btnImgHovered: "qrc:/GrayCatQtQuick/IconResource/RightButton_gray.svg"
            btnImgPressed: "qrc:/GrayCatQtQuick/IconResource/RightButton_gray.svg"
            btnImgDisbaled: "qrc:/GrayCatQtQuick/IconResource/RightButton_gray.svg"

        }

        CatButtonImage {
            id: nextYear
            anchors.verticalCenter: parent
            anchors.right: parent.right
            anchors.rightMargin: 5
            width: 25
            height: 25
            btnImgNormal: "qrc:/GrayCatQtQuick/IconResource/RightRightButton_default.svg"
            btnImgHovered: "qrc:/GrayCatQtQuick/IconResource/RightRightButton_gray.svg"
            btnImgPressed: "qrc:/GrayCatQtQuick/IconResource/RightRightButton_gray.svg"
            btnImgDisbaled: "qrc:/GrayCatQtQuick/IconResource/RightRightButton_gray.svg"

        }





    }



    function getMonthDay(year, month)
    {
        let days = new Date(year, month, 0).getDate();
        return days
    }
}
