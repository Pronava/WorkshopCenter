QT += core gui sql network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17

# Other configurations...

SOURCES += \
    chatwidget.cpp \
    databaseconnection.cpp \
    editaccount.cpp \
    main.cpp \
    client.cpp \
    registerwidget.cpp

HEADERS += \
    CustomWidgetItem.h \
    chatwidget.h \
    client.h \
    databaseconnection.h \
    editaccount.h \
    registerwidget.h

FORMS += \
    chatwidget.ui \
    client.ui \
    editaccount.ui \
    registerwidget.ui

TRANSLATIONS += \
    Client_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations
