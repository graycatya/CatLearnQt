import QtQuick
import QtQuick.Layouts
import QCatGrayQuick
import "../"
import LottieCompat as Lottie

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
