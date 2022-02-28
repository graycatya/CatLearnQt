#ifndef CATTABLEVIEWTOOL_H
#define CATTABLEVIEWTOOL_H

#include "CatControl/CatTableViewBasics.h"

class CatTableViewTool : public CatTableViewBasics
{
    Q_OBJECT
public:
    explicit CatTableViewTool(QWidget *parent = nullptr);
    ~CatTableViewTool();
};

#endif // CATTABLEVIEWTOOL_H
