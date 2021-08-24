#ifndef ENCPSSL_H
#define ENCPSSL_H

/*
 * 基于openssl加解密封装 作者:Graycatya(graycatya@163.com)
 * 1:Base64编解码
 * 2:Rsa非对称加解密
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <string>

class EncpSsl
{
public:
    EncpSsl();
    ~EncpSsl();

    //base64
    char * Base64Encode(const char * input, int length, bool with_new_line);
    char * Base64Decode(char * input, int length, bool with_new_line);
    std::string Base64Encode(const std::string input, bool with_new_line);
    std::string Base64Decode(std::string input, bool with_new_line);

    std::string Md5(const std::string input, bool length16 = false);

    //Rsa
    void Rsa_InitKey(int bits);
    std::string Rsa_Pub_Encrypt(const std::string &Text, std::string &PubKey);
    std::string Rsa_Pub_Decrypt(const std::string &Text, std::string &PubKey);
    std::string Rsa_Pri_Encrypt(const std::string &Text, std::string &PriKey);
    std::string Rsa_Pri_Decrypt(const std::string &Text, std::string &PriKey);
    std::string Get_Rsa_Pub_Key();
    std::string Get_Rsa_Pri_Key();

    //aes
    std::string Aes_128_Cbc_Encrypt(std::string in, std::string key);
    std::string Aes_128_Cbc_Decrypt(std::string in, std::string key);
    std::string Aes_192_Cbc_Encrypt(std::string in, std::string key);
    std::string Aes_192_Cbc_Decrypt(std::string in, std::string key);
    std::string Aes_256_Cbc_Encrypt(std::string in, std::string key);
    std::string Aes_256_Cbc_Decrypt(std::string in, std::string key);

    std::string Aes_128_Ecb_Encrypt(std::string in, std::string key);
    std::string Aes_128_Ecb_Decrypt(std::string in, std::string key);
    std::string Aes_192_Ecb_Encrypt(std::string in, std::string key);
    std::string Aes_192_Ecb_Decrypt(std::string in, std::string key);
    std::string Aes_256_Ecb_Encrypt(std::string in, std::string key);
    std::string Aes_256_Ecb_Decrypt(std::string in, std::string key);

    /*
      * 此功能用于md5生成后，进行行转码Hex
    */
    //StrToHex
    std::string StrToHex_Lowercase(const unsigned char* str, int length);
    std::string StrToHex_Capital(const unsigned char* str, int length);


protected:

private:
    //Rsa
    //RSA *m_pRsa;
    std::string m_sRsaPublic_Key;
    std::string m_sRsaPrivate_Key;

};

#endif // ENCPSSL_H
