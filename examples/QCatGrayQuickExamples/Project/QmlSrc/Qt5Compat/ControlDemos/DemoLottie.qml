import QtQuick 2.12
import QtQuick.Layouts 1.1
import QCatGrayQuick 1.0
import "../"
import LottieCompat 1.0 as Lottie

Rectangle {
    //id: demoimageflipable
    color: "transparent"

    Lottie.LottieAnimation {
        id: lottieAnim
        anchors.centerIn: parent
        width: implicitWidth
        height: implicitHeight
        source: "qrc:/Lottie/Lottie_404.json"
        running: true
        clearBeforeRendering: true
        speed: 1
        loops: Animation.Infinite
        fillMode: Image.Stretch
        reverse: false
    }
}
