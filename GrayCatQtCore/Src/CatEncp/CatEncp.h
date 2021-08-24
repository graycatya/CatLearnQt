#ifndef CATENCP_H
#define CATENCP_H

#include <QObject>
#include <QQmlEngine>


class EncpSsl;

class CatEncp : public QObject
{
    Q_OBJECT
public:
    explicit CatEncp(QObject *parent = nullptr);
    ~CatEncp() override;

public:
    Q_INVOKABLE static QString base64Encode(const QString input);
    Q_INVOKABLE static QString base64Decode(const QString input);

    // Rsa
    void rsa_InitKey(int bits);
    QString rsa_Pub_Encrypt(const QString Text, QString PubKey);
    QString rsa_Pub_Decrypt(const QString Text, QString PubKey);
    QString rsa_Pri_Encrypt(const QString Text, QString PriKey);
    QString rsa_Pri_Decrypt(const QString Text, QString PriKey);
    QString get_Rsa_Pub_Key();
    QString get_Rsa_Pri_Key();
    /*
      * 此功能用于md5生成后，进行行转码Hex
    */
    // 小端
    Q_INVOKABLE static QString strToHex_Lowercase(QString str);
    // 大端
    Q_INVOKABLE static QString strToHex_Capital(QString str);

    // md5
    Q_INVOKABLE static QString md5(QString input, bool length16 = false);

    // aes
    Q_INVOKABLE static QByteArray aes_128_Cbc_Encrypt(QByteArray in, QString key);
    Q_INVOKABLE static QByteArray aes_128_Cbc_Decrypt(QByteArray in, QString key);


    static CatEncp *qmlAttachedProperties(QObject *parent = nullptr);




private:
    EncpSsl* m_pEncpSsl = nullptr;
};

//! [declare attached]
QML_DECLARE_TYPEINFO(CatEncp, QML_HAS_ATTACHED_PROPERTIES)
//! [declare attached]

#endif // CATENCP_H
