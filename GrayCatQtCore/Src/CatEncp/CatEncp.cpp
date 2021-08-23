#include "CatEncp.h"
#include "Encp/encpssl.h"

CatEncp::CatEncp(QObject *parent) : QObject(parent)
{
    m_pEncpSsl = new EncpSsl;
}

CatEncp::~CatEncp()
{
    if(m_pEncpSsl != nullptr)
    {
        delete m_pEncpSsl;
        m_pEncpSsl = nullptr;
    }
}

QString CatEncp::base64Encode(const QString input)
{
    EncpSsl encp;
    QByteArray data = input.toLatin1();
    return QString::fromStdString(encp.Base64Encode(data.data(), data.length(), false));
}

QString CatEncp::base64Decode(const QString input)
{
    EncpSsl encp;
    QByteArray data = input.toLatin1();
    return QString::fromStdString(encp.Base64Decode(data.data(), data.length(), false));
}

void CatEncp::rsa_InitKey(int bits)
{
    m_pEncpSsl->Rsa_InitKey(bits);
}

QString CatEncp::rsa_Pub_Encrypt(const QString Text, QString PubKey)
{
    std::string pubkey = PubKey.toStdString();
    return QString::fromStdString(m_pEncpSsl->Rsa_Pub_Encrypt(Text.toStdString(),
                                                              pubkey));
}

QString CatEncp::rsa_Pub_Decrypt(const QString Text, QString PubKey)
{
    std::string pubkey = PubKey.toStdString();
    return QString::fromStdString(m_pEncpSsl->Rsa_Pub_Decrypt(Text.toStdString(),
                                                              pubkey));
}

QString CatEncp::rsa_Pri_Encrypt(const QString Text, QString PriKey)
{
    std::string pubkey = PriKey.toStdString();
    return QString::fromStdString(m_pEncpSsl->Rsa_Pri_Encrypt(Text.toStdString(),
                                                              pubkey));
}

QString CatEncp::rsa_Pri_Decrypt(const QString Text, QString PriKey)
{
    std::string pubkey = PriKey.toStdString();
    return QString::fromStdString(m_pEncpSsl->Rsa_Pri_Decrypt(Text.toStdString(),
                                                              pubkey));
}

QString CatEncp::get_Rsa_Pub_Key()
{
    return QString::fromStdString(m_pEncpSsl->Get_Rsa_Pub_Key());
}

QString CatEncp::get_Rsa_Pri_Key()
{
    return QString::fromStdString(m_pEncpSsl->Get_Rsa_Pri_Key());
}

QString CatEncp::strToHex_Lowercase(QString str)
{
    EncpSsl encp;
    QByteArray data = str.toLatin1();
    return QString::fromStdString(encp.StrToHex_Lowercase((unsigned char*)(data.data()), data.length()));
}

QString CatEncp::strToHex_Capital(QString str)
{
    EncpSsl encp;
    QByteArray data = str.toLatin1();
    return QString::fromStdString(encp.StrToHex_Capital((unsigned char*)(data.data()), data.length()));
}

QString CatEncp::md5(QString input, bool length16)
{
    EncpSsl encp;
    return QString::fromStdString(encp.Md5(input.toStdString(), length16));
}


CatEncp *CatEncp::qmlAttachedProperties(QObject *object)
{
    return new CatEncp(object);
}


