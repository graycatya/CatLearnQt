import QtQuick 2.12
import QtQuick.Shapes 1.12

Rectangle {
    id: catRectangle
    readonly property string version: "1.0"
    property bool leftTopRound: true
    property bool leftBottomRound: true
    property bool rightTopRound: true
    property bool rightBottomRound: true

    property real backdropRadius: 0
    property color backdropColor: "#FFFFFF"
    property real borderWidth: 0
    property color borderColor: "transparent"

    property real radius: 0
    //property color color: "transparent"
    //property color bordercolor: border.color = "transparent"
    //readonly property real border:

    color: "transparent"
    border.color: "transparent"
    border.width: 0

    Shape {

        id: catRectangleShape
        anchors.fill: catRectangle
        layer.enabled: true
        layer.samples: 8
        smooth: true
        antialiasing: true
        asynchronous: true

        ShapePath {
            fillColor: catRectangle.backdropColor
            startX: catRectangle.leftTopRound ? catRectangle.backdropRadius : 0
            startY: 0
            fillRule: ShapePath.WindingFill
            strokeColor: catRectangle.borderColor
            strokeStyle: ShapePath.RoundJoin
            strokeWidth: catRectangle.borderWidth
            PathLine {
                x: catRectangle.rightTopRound ?
                       catRectangle.width - catRectangle.backdropRadius
                     : catRectangle.width
                y: 0
            }
            PathArc {
                x: catRectangle.width
                y: catRectangle.rightTopRound ?
                       catRectangle.backdropRadius
                     : 0
                radiusX: catRectangle.rightTopRound ?
                             catRectangle.backdropRadius
                           : 0
                radiusY: catRectangle.rightTopRound ?
                             catRectangle.backdropRadius
                           : 0
            }

            PathLine {
                x: catRectangle.width
                y: catRectangle.rightBottomRound ?
                       catRectangle.height - catRectangle.backdropRadius
                     : catRectangle.height
            }
            PathArc {
                x: catRectangle.rightBottomRound ?
                       catRectangle.width - catRectangle.backdropRadius
                     : catRectangle.width
                y: catRectangle.height
                radiusX: catRectangle.rightBottomRound ? catRectangle.backdropRadius : 0
                radiusY: catRectangle.rightBottomRound ? catRectangle.backdropRadius : 0
            }

            PathLine {
                x: catRectangle.leftBottomRound ? catRectangle.backdropRadius : 0
                y: catRectangle.height
            }
            PathArc {
                x: 0
                y: catRectangle.leftBottomRound ?
                       catRectangle.height - catRectangle.backdropRadius
                     : catRectangle.height
                radiusX: catRectangle.leftBottomRound ? catRectangle.backdropRadius : 0
                radiusY: catRectangle.leftBottomRound ? catRectangle.backdropRadius : 0
            }

            PathLine {
                x: 0
                y: catRectangle.leftTopRound ? catRectangle.backdropRadius : 0
            }
            PathArc {
                x: catRectangle.leftTopRound ? catRectangle.backdropRadius : 0
                y: 0
                radiusX: catRectangle.leftTopRound ? catRectangle.backdropRadius : 0
                radiusY: catRectangle.leftTopRound ? catRectangle.backdropRadius : 0
            }
        }
    }
}
