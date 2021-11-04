import QtQuick 2.12
import QtQuick.Controls 2.12
import QtWebEngine 1.8

Item {
    id: webengineLicence
    WebEngineView {
        id: licencetext
        anchors.fill: parent
        anchors.bottomMargin: 10
        url: "qrc:/Licence/Licence.html"
        backgroundColor: "transparent"
    }
}
