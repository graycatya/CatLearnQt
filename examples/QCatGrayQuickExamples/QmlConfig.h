#ifndef QMLCONFIG_H
#define QMLCONFIG_H

#include "Src/TableFunction/TableViewModel.h"
#include "CatModel/CatListModel.h"
#include "CatModel/CatTreeModel.h"
#include "CatModel/ModelTools.h"
#include <QQmlContext>
#include <QQmlEngine>
#include <QmlCatLog.h>
#include <QQuickView>


namespace QmlConfig {

    static void moduleRegister()
    {
        qmlRegisterType<TableViewModel>("TableViewModel",1,0,"TableViewModel");
        qmlRegisterType<CatModel::CatTreeModel>("CatTreeModel", 1, 0, "CatTreeModel");
        qmlRegisterType<CatModel::ModelTool>("ModelTool", 1, 0, "ModelTool");
    }
}

#endif // QMLCONFIG_H
