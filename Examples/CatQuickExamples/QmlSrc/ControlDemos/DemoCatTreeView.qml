import QtQuick 2.12
import CatTreeModel 1.0
import ModelTool 1.0
import "../Common"

Item {
    id: democattreeview

    CatTreeModel {
        id: cattreemodel
        onShowMessage: {

        }
    }

    CatTreeView {
        id: cattreeview
    }

}
