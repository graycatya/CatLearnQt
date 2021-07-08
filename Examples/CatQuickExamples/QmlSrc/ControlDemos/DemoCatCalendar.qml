import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12
import GrayCatQtQuick 1.0
import "../"

Rectangle {
    //id: demoimageflipable
    color: "transparent"

    CatCalendar {
        id: catcalendar
        anchors.centerIn: parent

        preiousYearButton.btnImgNormal: ProjectObject.getCurrentResourcePath() + "LeftLeftButton_default.svg"
        preiousYearButton.btnImgHovered: ProjectObject.getCurrentResourcePath() + "LeftLeftButton_gray.svg"
        preiousYearButton.btnImgPressed: ProjectObject.getCurrentResourcePath() + "LeftLeftButton_gray.svg"
        preiousYearButton.btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "LeftLeftButton_gray.svg"

        lastMonthButton.btnImgNormal: ProjectObject.getCurrentResourcePath() + "LeftButton_default.svg"
        lastMonthButton.btnImgHovered: ProjectObject.getCurrentResourcePath() + "LeftButton_gray.svg"
        lastMonthButton.btnImgPressed: ProjectObject.getCurrentResourcePath() + "LeftButton_gray.svg"
        lastMonthButton.btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "LeftButton_gray.svg"

        nextMonthButton.btnImgNormal: ProjectObject.getCurrentResourcePath() + "RightButton_default.svg"
        nextMonthButton.btnImgHovered: ProjectObject.getCurrentResourcePath() + "RightButton_gray.svg"
        nextMonthButton.btnImgPressed: ProjectObject.getCurrentResourcePath() + "RightButton_gray.svg"
        nextMonthButton.btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "RightButton_gray.svg"

        nextYearButton.btnImgNormal: ProjectObject.getCurrentResourcePath() + "RightRightButton_default.svg"
        nextYearButton.btnImgHovered: ProjectObject.getCurrentResourcePath() + "RightRightButton_gray.svg"
        nextYearButton.btnImgPressed: ProjectObject.getCurrentResourcePath() + "RightRightButton_gray.svg"
        nextYearButton.btnImgDisbaled: ProjectObject.getCurrentResourcePath() + "RightRightButton_gray.svg"



    }

    DropShadow {
        anchors.fill: catcalendar
        horizontalOffset: 0
        verticalOffset: 0
        radius: 10.0
        samples: 16
        color: "#3FFFFFFF"
        source: catcalendar
    }
}
