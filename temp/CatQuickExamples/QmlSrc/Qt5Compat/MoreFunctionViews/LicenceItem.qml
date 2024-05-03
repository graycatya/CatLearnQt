import QtQuick 2.12
import QtQuick.Controls 2.12
//import QtWebEngine 1.8
import "../"

Item {
    id: licenceitem

    Loader {
        id: licenceLoader
        anchors.fill: licenceitem
        asynchronous: true
        visible: status == Loader.Ready
        onProgressChanged: {
            console.log("Licence Progress: " + progress)
        }
    }

    Component.onCompleted: {
        if(catconfig.qtWebEngine())
        {
            licenceLoader.source = "./WebEngineLicence.qml";
        } else {
            licenceLoader.source = "./WebKitLicence.qml";
        }
    }
}
