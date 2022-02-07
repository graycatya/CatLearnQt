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
#include "utilities.h"
#include "framelessquickhelper.h"
#include "utilities.h"
#include "framelessquickhelper.h"

FRAMELESSHELPER_USE_NAMESPACE

static constexpr const char qtquicknamespace[] = "wangwenx190.Utils";

class UtilFunctions : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(UtilFunctions)
    Q_PROPERTY(bool isWindowsHost READ isWindowsHost CONSTANT)
    Q_PROPERTY(bool isWindows10OrGreater READ isWindows10OrGreater CONSTANT)
    Q_PROPERTY(bool isWindows11OrGreater READ isWindows11OrGreater CONSTANT)
    Q_PROPERTY(QColor activeFrameBorderColor READ activeFrameBorderColor CONSTANT)
    Q_PROPERTY(QColor inactiveFrameBorderColor READ inactiveFrameBorderColor CONSTANT)
    Q_PROPERTY(qreal frameBorderThickness READ frameBorderThickness CONSTANT)

public:
    explicit UtilFunctions(QObject *parent = nullptr) : QObject(parent) {}
    ~UtilFunctions() override = default;

    inline bool isWindowsHost() const {
#ifdef Q_OS_WINDOWS
        return true;
#else
        return false;
#endif
    }

    inline bool isWindows10OrGreater() const {
#ifdef Q_OS_WINDOWS
        return Utilities::isWin10OrGreater();
#else
        return false;
#endif
    }

    inline bool isWindows11OrGreater() const {
#ifdef Q_OS_WINDOWS
        return Utilities::isWin11OrGreater();
#else
        return false;
#endif
    }

    inline QColor activeFrameBorderColor() const {
        const ColorizationArea area = Utilities::getColorizationArea();
        const bool colorizedBorder = ((area == ColorizationArea::TitleBar_WindowBorder)
                                      || (area == ColorizationArea::All));
        return (colorizedBorder ? Utilities::getColorizationColor() : Qt::black);
    }

    inline QColor inactiveFrameBorderColor() const {
        return Qt::darkGray;
    }

    inline qreal frameBorderThickness() const {
        return 1.0;
    }
};

namespace QmlConfig {

    static void moduleRegister()
    {
        qmlRegisterType<TableViewModel>("TableViewModel",1,0,"TableViewModel");
        qmlRegisterType<CatModel::CatTreeModel>("CatTreeModel", 1, 0, "CatTreeModel");
        qmlRegisterType<CatModel::ModelTool>("ModelTool", 1, 0, "ModelTool");
        qmlRegisterSingletonType<UtilFunctions>(qtquicknamespace, 1, 0, "Utils", [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
            Q_UNUSED(engine);
            Q_UNUSED(scriptEngine);
            return new UtilFunctions();
        });
        qmlRegisterType<FramelessQuickHelper>(qtquicknamespace, 1, 0, "FramelessHelper");

    }
}

#endif // QMLCONFIG_H
