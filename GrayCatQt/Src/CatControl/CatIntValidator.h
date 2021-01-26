#ifndef CATINTVALIDATOR_H
#define CATINTVALIDATOR_H

#include <QIntValidator>

class CatIntValidator : public QIntValidator
{
    Q_OBJECT
public:
    explicit CatIntValidator(QObject *parent = nullptr);
    ~CatIntValidator();

public:
    virtual QValidator::State validate(QString &input, int &pos) const override;
    virtual void fixup(QString &input) const override;
};

#endif // CATINTVALIDATOR_H
