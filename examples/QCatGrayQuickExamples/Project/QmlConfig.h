#ifndef QMLCONFIG_H
#define QMLCONFIG_H

#include "TableViewModel.h"
//#include "QCatGrayListModel.h"
#include "QCatGrayTreeModel.h"
#include "QCatGrayModelTools.h"
#include "QCatGrayChatStruct.h"
#include "QCatGrayQuickChatModel.h"
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>


namespace QmlConfig {

    static void moduleRegister()
    {
        qmlRegisterType<TableViewModel>("TableViewModel",1,0,"TableViewModel");
        qmlRegisterType<QCatGrayTreeModel>("CatTreeModel", 1, 0, "CatTreeModel");
        qmlRegisterType<QCatGrayModel::ModelTool>("ModelTool", 1, 0, "ModelTool");
        qmlRegisterType<QCatGrayChatStruct>("QCatGrayChatStruct", 1, 0, "ChatStruct");
        qmlRegisterType<QCatGrayQuickChatModel>("QCatGrayQuickChatModel", 1, 0, "QCatGrayQuickChatModel");
    }
}

#endif // QMLCONFIG_H
