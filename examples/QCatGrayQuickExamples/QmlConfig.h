#ifndef QMLCONFIG_H
#define QMLCONFIG_H

#include "TableViewModel.h"
//#include "QCatGrayListModel.h"
////#include "QCatGrayTreeModel.h"
#include "QCatGrayModelTools.h"
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>


namespace QmlConfig {

    static void moduleRegister()
    {
        qmlRegisterType<TableViewModel>("TableViewModel",1,0,"TableViewModel");
        //qmlRegisterType<QCatGrayListModel<QJsonObject>>("CatTreeModel", 1, 0, "CatTreeModel");
        qmlRegisterType<QCatGrayModel::ModelTool>("ModelTool", 1, 0, "ModelTool");
    }
}

#endif // QMLCONFIG_H
