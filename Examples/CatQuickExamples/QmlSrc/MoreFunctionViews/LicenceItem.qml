import QtQuick 2.12
import QtQuick.Controls 2.12
import QtWebEngine 1.8
import "../"

Item {
    id: licenceitem

        WebEngineView {
            id: licencetext
            anchors.fill: parent
            anchors.bottomMargin: 10
            url: "qrc:/Licence/Licence.html"
            backgroundColor: "transparent"
            //anchors.fill: parent
            //anchors.leftMargin: 10
            //anchors.rightMargin: 10


        }
}
