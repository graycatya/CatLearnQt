import QtQuick
import QtQuick3D
import "../"

Rectangle {
    id: image3drotation
    color: "transparent"

    View3D {
        id: view
        anchors.fill: parent
        camera: camera
        renderMode: View3D.Overlay
        width: 250
        height: 250

        PerspectiveCamera {
            id: camera
            position: Qt.vector3d(0, 250, 250)
            eulerRotation.x: -45
        }

        DirectionalLight {
            eulerRotation.x: -45
        }

        Model {
            //! [3dcube]
            id: cube
            visible: true
            position: Qt.vector3d(0, 0, 0)
            source: "#Cube"
            /*materials: DefaultMaterial {
                }*/

            Node {

                Image {
                    source: ProjectObject.resourcePath +  "qt_logo.png"
                    width: 250
                    height: 250

                }

            }
            eulerRotation.y: 90
            //! [3dcube]

            SequentialAnimation on eulerRotation {
                loops: Animation.Infinite
                PropertyAnimation {
                    duration: 5000
                    from: Qt.vector3d(0, 0, 0)
                    to: Qt.vector3d(360, 0, 360)
                }
            }
        }
    }
}
