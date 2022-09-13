import QtQuick
import QtQuick.Shapes

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

            startX: catRectangle.leftTopRound ?
                        catRectangle.backdropRadius + catRectangle.borderWidth
                      : 0 + catRectangle.borderWidth
            startY: 0 + catRectangle.borderWidth

            fillRule: ShapePath.WindingFill
            joinStyle: ShapePath.RoundJoin
            strokeColor: catRectangle.borderColor
            strokeWidth: catRectangle.borderWidth

            PathLine {
                x: catRectangle.rightTopRound ?
                       catRectangle.width - catRectangle.backdropRadius - catRectangle.borderWidth
                     : catRectangle.width - catRectangle.borderWidth
                y: 0 + catRectangle.borderWidth
            }
            PathArc {
                x: catRectangle.width - catRectangle.borderWidth
                y: catRectangle.rightTopRound ?
                       catRectangle.backdropRadius + catRectangle.borderWidth
                     : 0 + catRectangle.borderWidth
                radiusX: catRectangle.rightTopRound ?
                             catRectangle.backdropRadius
                           : 0
                radiusY: catRectangle.rightTopRound ?
                             catRectangle.backdropRadius
                           : 0
            }

            PathLine {
                x: catRectangle.width - catRectangle.borderWidth
                y: catRectangle.rightBottomRound ?
                       catRectangle.height - catRectangle.backdropRadius - catRectangle.borderWidth
                     : catRectangle.height - catRectangle.borderWidth
            }
            PathArc {
                x: catRectangle.rightBottomRound ?
                       catRectangle.width - catRectangle.backdropRadius - catRectangle.borderWidth
                     : catRectangle.width - catRectangle.borderWidth
                y: catRectangle.height - catRectangle.borderWidth

                radiusX: catRectangle.rightBottomRound ?
                             catRectangle.backdropRadius
                           : 0
                radiusY: catRectangle.rightBottomRound ?
                             catRectangle.backdropRadius
                           : 0
            }

            PathLine {
                x: catRectangle.leftBottomRound ?
                       catRectangle.backdropRadius + catRectangle.borderWidth
                     : 0 + catRectangle.borderWidth
                y: catRectangle.height - catRectangle.borderWidth
            }
            PathArc {
                x: 0 + catRectangle.borderWidth
                y: catRectangle.leftBottomRound ?
                       catRectangle.height - catRectangle.backdropRadius - catRectangle.borderWidth
                     : catRectangle.height - catRectangle.borderWidth

                radiusX: catRectangle.leftBottomRound ?
                             catRectangle.backdropRadius
                         : 0
                radiusY: catRectangle.leftBottomRound ?
                             catRectangle.backdropRadius
                           : 0
            }

            PathLine {
                x: 0 + catRectangle.borderWidth
                y: catRectangle.leftTopRound ?
                       catRectangle.backdropRadius + catRectangle.borderWidth
                     : 0 + catRectangle.borderWidth
            }
            PathArc {
                x: catRectangle.leftTopRound ?
                       catRectangle.backdropRadius + catRectangle.borderWidth
                     : 0 - catRectangle.borderWidth
                y: 0 + catRectangle.borderWidth
                radiusX: catRectangle.leftTopRound ?
                             catRectangle.backdropRadius
                           : 0
                radiusY: catRectangle.leftTopRound ?
                             catRectangle.backdropRadius
                           : 0
            }
        }
    }
}
