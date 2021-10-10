#ifndef CATTREEMODEL_H
#define CATTREEMODEL_H

#include "CatListModel.h"
#include <QJsonObject>

namespace CatModel {

const static QString ModelDepthKey = QStringLiteral("TreeModel_depth");
const static QString ModelExpendKey = QStringLiteral("TreeModel_expend");
const static QString ModelChildrenExpendKey = QStringLiteral("TreeModel_childrenExpend");
const static QString ModelHasChildrendKey = QStringLiteral("TreeModel_hasChildren");
const static QString ModelParentKey = QStringLiteral("TreeModel_parent");
const static QString ModelChildrenKey = QStringLiteral("TreeModel_children");

const static QString ModelRecursionKey = QStringLiteral("subType");
const static QStringList ModelFilterKeyList = { ModelDepthKey, ModelExpendKey,
                                              ModelChildrenExpendKey, ModelHasChildrendKey,
                                              ModelParentKey, ModelChildrenKey };

class CatTreeModel
{
public:
    CatTreeModel();
};

}


#endif // CATTREEMODEL_H
