import QtQuick
import QtQuick.Controls
import QtWebEngine

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
