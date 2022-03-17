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

#include "framelessquickhelper.h"

static constexpr const char qtquicknamespace[] = "GrayFramelesshelper.Utils";

namespace QmlConfig {

    static void moduleRegister()
    {
        qmlRegisterType<TableViewModel>("TableViewModel",1,0,"TableViewModel");
        qmlRegisterType<CatModel::CatTreeModel>("CatTreeModel", 1, 0, "CatTreeModel");
        qmlRegisterType<CatModel::ModelTool>("ModelTool", 1, 0, "ModelTool");
        qmlRegisterType<FRAMELESSHELPER_PREPEND_NAMESPACE(FramelessQuickHelper)>(qtquicknamespace, 1, 0, "FramelessHelper");
    }
}

#endif // QMLCONFIG_H
