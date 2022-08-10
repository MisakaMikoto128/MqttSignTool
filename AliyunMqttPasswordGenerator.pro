QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        hash-library/crc32.cpp \
        hash-library/keccak.cpp \
        hash-library/md5.cpp \
        hash-library/sha1.cpp \
        hash-library/sha256.cpp \
        hash-library/sha3.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    hash-library/crc32.h \
    hash-library/hash.h \
    hash-library/hmac.h \
    hash-library/keccak.h \
    hash-library/md5.h \
    hash-library/sha1.h \
    hash-library/sha256.h \
    hash-library/sha3.h
