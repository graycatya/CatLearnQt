#include "CatDoubleValidator.h"
#include <QDebug>


CatDoubleValidator::CatDoubleValidator(QObject *parent)
    :QDoubleValidator(parent)
{

}

CatDoubleValidator::~CatDoubleValidator()
{

}

QValidator::State CatDoubleValidator::validate(QString &input, int &pos) const
{
    Q_UNUSED(pos)
    if (input.isEmpty())
    {
        return QValidator::Intermediate;
    }
    if(bottom()<0 && input=="-")
        return QValidator::Intermediate;

    bool cOK = false;
    double val = input.toDouble(&cOK);

    if (!cOK)
    {
        return QValidator::Invalid;
    }

    int dotPos = input.indexOf(".");
    if (dotPos > 0)
    {
        if (input.right(input.length() - dotPos-1).length() > decimals())
        {
            return QValidator::Invalid;
        }
    }
    if (val<= top() && val >= bottom())
    {
        return QValidator::Acceptable;
    }
    else if(val>top())
    {
        return QValidator::Invalid;
    }
    else if(val<bottom())
    {
        return QValidator::Invalid;
    }
    return QValidator::Invalid;
}

void CatDoubleValidator::fixup(QString &input) const
{
    if(input.toDouble()<bottom())
    {
        QString *str=&input;
        *str=QString::number(bottom());
    }
}
