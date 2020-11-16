#ifndef QTQMLPARENTQRENCODE_H
#define QTQMLPARENTQRENCODE_H

#include <QQuickPaintedItem>
#include "../../qrencode.h"

class QuickQrenCodeParentItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText)
    Q_PROPERTY(QString source READ getLogo WRITE setLogo)
    Q_PROPERTY(QR_MODE qrmode READ getQrmode WRITE setQrmode)
    Q_PROPERTY(QR_LEVEL qrlevel READ getQrlevel WRITE setQrlevel)
    Q_PROPERTY(bool casesen READ getCasesen WRITE setCasesen)
    Q_PROPERTY(qreal qrpercent READ getQrPercent WRITE setQrPercent)
    Q_ENUMS(QR_MODE)
    Q_ENUMS(QR_LEVEL)

public:
    enum QR_MODE {
        MODE_NUL = QR_MODE_NUL,
        MODE_NUM = QR_MODE_NUM,
        MODE_AN = QR_MODE_AN,
        MODE_8 = QR_MODE_8,
        MODE_KANJI = QR_MODE_KANJI,
        MODE_STRUCTURE = QR_MODE_STRUCTURE,
        MODE_ECI = QR_MODE_ECI,
        MODE_FNC1FIRST = QR_MODE_FNC1FIRST,
        MODE_FNC1SECOND = QR_MODE_FNC1SECOND
    };

    enum QR_LEVEL {
        LEVEL_L = QR_ECLEVEL_L,
        LEVEL_M = QR_ECLEVEL_M,
        LEVEL_Q = QR_ECLEVEL_Q,
        LEVEL_H = QR_ECLEVEL_H
    };

    explicit QuickQrenCodeParentItem(QQuickItem *parent = nullptr);
    ~QuickQrenCodeParentItem() override;

    inline QString getText() const
    {
        return m_sText;
    }

    inline void setText(QString text)
    {
        m_sText = text;
        update();
    }

    inline QString getLogo() const
    {
        return m_sQrLogo;
    }

    inline void setLogo(QString source)
    {
        m_sQrLogo = source;
        update();
    }

    inline QR_MODE getQrmode() const
    {
        return m_eQrmode;
    }

    inline void setQrmode(QR_MODE mode)
    {
        m_eQrmode = mode;
        update();
    }

    inline QR_LEVEL getQrlevel() const
    {
        return m_eQrlevel;
    }

    inline void setQrlevel(QR_LEVEL level)
    {
        m_eQrlevel = level;
        update();
    }

    inline bool getCasesen() const
    {
        return m_bCasesen;
    }

    inline void setCasesen(bool casesen)
    {
        m_bCasesen = casesen;
        update();
    }

    inline qreal getQrPercent() const
    {
        return m_qQrPercent;
    }

    inline void setQrPercent(qreal qrpercent)
    {
        m_qQrPercent = qrpercent;
        update();
    }

protected:
    void paint(QPainter *painter) override;

private:
    void InitProperty();


private:
    QString m_sText;
    QString m_sQrLogo;
    QR_MODE m_eQrmode;
    QR_LEVEL m_eQrlevel;
    qreal m_qQrPercent;
    bool m_bCasesen;

};

#endif // QTQMLPARENTQRENCODE_H
