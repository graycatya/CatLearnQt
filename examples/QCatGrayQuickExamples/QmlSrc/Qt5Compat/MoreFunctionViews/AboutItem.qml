import QtQuick 2.12
import QtQuick.Layouts 1.12
import "../"
import QCatGrayQuick 1.0


Item {
    id: aboutitem

    ColumnLayout {
        anchors.fill: parent
        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 250
            //horizontalCenter: parent.horizontalCenter
            CatBasicsText {
                id: apptext
                anchors.left: parent.left
                anchors.right: parent.right
                text: catconfig.getAppName() + " " + catconfig.getAppVersion()
                color: ProjectObject.defaultTextColor
                font.pixelSize: 32
                font.family: ProjectObject.fontFamily
                font.bold: true
            }
            CatBasicsText {
                id: explaintext
                anchors.top: apptext.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.topMargin: 5
                text: qsTr("This software is used to learn Qt development.")
                color: ProjectObject.defaultTextColor
                font.pixelSize: 14
                font.family: ProjectObject.fontFamily
            }

            CatBasicsText {
                id: qtversiontext
                anchors.top: explaintext.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.topMargin: 5
                text: "Qt " + catconfig.getQtVersion();
                color: ProjectObject.defaultTextColor
                font.pixelSize: 12
                font.family: ProjectObject.fontFamily
            }

            CatBasicsText {
                id: authortext
                anchors.top: explaintext.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.topMargin: 120
                text: qsTr("Author: ") + "GrayCatYa"
                color: ProjectObject.defaultTextColor
                font.pixelSize: 14
                font.family: ProjectObject.fontFamily
                font.bold: true
            }

            RowLayout {
                anchors.top: authortext.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 30
                anchors.topMargin: 5
                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
                CatButtonImage {
                    imagebackground.radius: 5
                    backgroundColor: "#01000000"
                    backgroundColor_pressed: "#66000000"
                    backgroundColor_hovered: "#40000000"
                    Layout.preferredHeight: 30
                    Layout.preferredWidth: 30
                    btnImgUrl: ProjectObject.getCurrentResourcePath() + "CodeChina.png"
                    onClicked: {
                        catconfig.openWebUrl(ProjectObject.codeChinaUrl);
                    }
                }

                CatButtonImage {
                    imagebackground.radius: 5
                    backgroundColor: "#01000000"
                    backgroundColor_pressed: "#66000000"
                    backgroundColor_hovered: "#40000000"
                    Layout.preferredHeight: 30
                    Layout.preferredWidth: 30
                    btnImgUrl: ProjectObject.getCurrentResourcePath() + "Github.png"
                    onClicked: {
                        catconfig.openWebUrl(ProjectObject.githubUrl);
                    }
                }

//                CatButtonImage {
//                    imagebackground.radius: 5
//                    backgroundColor: "#01000000"
//                    backgroundColor_pressed: "#66000000"
//                    backgroundColor_hovered: "#40000000"
//                    Layout.preferredHeight: 30
//                    Layout.preferredWidth: 30
//                    btnImgUrl: ProjectObject.getCurrentResourcePath() + "Gitee.png"
//                    onClicked: {
//                        catconfig.openWebUrl(ProjectObject.giteeUrl);
//                    }
//                }

                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }

            }
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
