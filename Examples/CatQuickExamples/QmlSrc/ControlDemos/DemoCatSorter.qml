import QtQuick 2.12
import GrayCatQtQuick 1.0
import QtQuick.Layouts 1.12

Rectangle {
    id: root
    //id: demoimageflipable
    color: "transparent"

    ColumnLayout {
        id: columnlayout
        spacing: 10

        CatSorter {
            id: sorterdemo0
            totalData: 1000
            pageDataSize: 100
        }
    }

}
