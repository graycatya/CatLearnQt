HEADERS += \
    $$PWD/CatEncp.h \
    $$PWD/Encp/encpssl.h \
    $$PWD/openssl/__DECC_INCLUDE_EPILOGUE.H \
    $$PWD/openssl/__DECC_INCLUDE_PROLOGUE.H \
    $$PWD/openssl/aes.h \
    $$PWD/openssl/asn1.h \
    $$PWD/openssl/asn1_mac.h \
    $$PWD/openssl/asn1err.h \
    $$PWD/openssl/asn1t.h \
    $$PWD/openssl/async.h \
    $$PWD/openssl/asyncerr.h \
    $$PWD/openssl/bio.h \
    $$PWD/openssl/bioerr.h \
    $$PWD/openssl/blowfish.h \
    $$PWD/openssl/bn.h \
    $$PWD/openssl/bnerr.h \
    $$PWD/openssl/buffer.h \
    $$PWD/openssl/buffererr.h \
    $$PWD/openssl/camellia.h \
    $$PWD/openssl/cast.h \
    $$PWD/openssl/cmac.h \
    $$PWD/openssl/cms.h \
    $$PWD/openssl/cmserr.h \
    $$PWD/openssl/comp.h \
    $$PWD/openssl/comperr.h \
    $$PWD/openssl/conf.h \
    $$PWD/openssl/conf_api.h \
    $$PWD/openssl/conferr.h \
    $$PWD/openssl/crypto.h \
    $$PWD/openssl/cryptoerr.h \
    $$PWD/openssl/ct.h \
    $$PWD/openssl/cterr.h \
    $$PWD/openssl/des.h \
    $$PWD/openssl/dh.h \
    $$PWD/openssl/dherr.h \
    $$PWD/openssl/dsa.h \
    $$PWD/openssl/dsaerr.h \
    $$PWD/openssl/dtls1.h \
    $$PWD/openssl/e_os2.h \
    $$PWD/openssl/ebcdic.h \
    $$PWD/openssl/ec.h \
    $$PWD/openssl/ecdh.h \
    $$PWD/openssl/ecdsa.h \
    $$PWD/openssl/ecerr.h \
    $$PWD/openssl/engine.h \
    $$PWD/openssl/engineerr.h \
    $$PWD/openssl/err.h \
    $$PWD/openssl/evp.h \
    $$PWD/openssl/evperr.h \
    $$PWD/openssl/hmac.h \
    $$PWD/openssl/idea.h \
    $$PWD/openssl/kdf.h \
    $$PWD/openssl/kdferr.h \
    $$PWD/openssl/lhash.h \
    $$PWD/openssl/md2.h \
    $$PWD/openssl/md4.h \
    $$PWD/openssl/md5.h \
    $$PWD/openssl/mdc2.h \
    $$PWD/openssl/modes.h \
    $$PWD/openssl/obj_mac.h \
    $$PWD/openssl/objects.h \
    $$PWD/openssl/objectserr.h \
    $$PWD/openssl/ocsp.h \
    $$PWD/openssl/ocsperr.h \
    $$PWD/openssl/opensslconf.h \
    $$PWD/openssl/opensslv.h \
    $$PWD/openssl/ossl_typ.h \
    $$PWD/openssl/pem.h \
    $$PWD/openssl/pem2.h \
    $$PWD/openssl/pemerr.h \
    $$PWD/openssl/pkcs12.h \
    $$PWD/openssl/pkcs12err.h \
    $$PWD/openssl/pkcs7.h \
    $$PWD/openssl/pkcs7err.h \
    $$PWD/openssl/rand.h \
    $$PWD/openssl/rand_drbg.h \
    $$PWD/openssl/randerr.h \
    $$PWD/openssl/rc2.h \
    $$PWD/openssl/rc4.h \
    $$PWD/openssl/rc5.h \
    $$PWD/openssl/ripemd.h \
    $$PWD/openssl/rsa.h \
    $$PWD/openssl/rsaerr.h \
    $$PWD/openssl/safestack.h \
    $$PWD/openssl/seed.h \
    $$PWD/openssl/sha.h \
    $$PWD/openssl/srp.h \
    $$PWD/openssl/srtp.h \
    $$PWD/openssl/ssl.h \
    $$PWD/openssl/ssl2.h \
    $$PWD/openssl/ssl3.h \
    $$PWD/openssl/sslerr.h \
    $$PWD/openssl/stack.h \
    $$PWD/openssl/store.h \
    $$PWD/openssl/storeerr.h \
    $$PWD/openssl/symhacks.h \
    $$PWD/openssl/tls1.h \
    $$PWD/openssl/ts.h \
    $$PWD/openssl/tserr.h \
    $$PWD/openssl/txt_db.h \
    $$PWD/openssl/ui.h \
    $$PWD/openssl/uierr.h \
    $$PWD/openssl/whrlpool.h \
    $$PWD/openssl/x509.h \
    $$PWD/openssl/x509_vfy.h \
    $$PWD/openssl/x509err.h \
    $$PWD/openssl/x509v3.h \
    $$PWD/openssl/x509v3err.h

#SOURCES += \
#    $$PWD/openssl/applink.c

SOURCES += \
    $$PWD/CatEncp.cpp \
    $$PWD/Encp/encpssl.cpp

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32 {

CONFIG += debug_and_release

contains(DEFINES, WIN64) {
    # 64
    LIBS += -L$$PWD/lib/x64/ -llibcrypto -llibssl
} else {
    # 32
    LIBS += -L$$PWD/lib/x32/ -llibcrypto -llibssl
}

}

unix {
    LIBS += -L$$PWD/lib/ -lcrypto -lssl
}
