#ifndef CATDOUBLEVALIDATOR_H
#define CATDOUBLEVALIDATOR_H

#include <QDoubleValidator>

class CatDoubleValidator : public QDoubleValidator
{
    Q_OBJECT
public:
    explicit CatDoubleValidator(QObject *parent = nullptr);
    ~CatDoubleValidator();

public:

    virtual QValidator::State validate(QString &input, int &pos) const override;
    virtual void fixup(QString &input) const override;

};

#endif // CATDOUBLEVALIDATOR_H
