QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminform.cpp \
    allHCform.cpp \
    allbeekeeperform.cpp \
    allclientform.cpp \
    allcolonyform.cpp \
    allhiveform.cpp \
    beekeeperform.cpp \
    buyform.cpp \
    clientform.cpp \
    databasemanager.cpp \
    editbeekeeperform.cpp \
    editclientform.cpp \
    loginform.cpp \
    main.cpp \
    manageHCform.cpp \
    managecoloniesform.cpp \
    managehivesform.cpp \
    orderhistoryform.cpp \
    registerclientform.cpp \
    startwindow.cpp

HEADERS += \
    adminform.h \
    allHCform.h \
    allbeekeeperform.h \
    allclientform.h \
    allcolonyform.h \
    allhiveform.h \
    beekeeperform.h \
    buyform.h \
    clientform.h \
    databasemanager.h \
    editbeekeeperform.h \
    editclientform.h \
    loginform.h \
    manageHCform.h \
    managecoloniesform.h \
    managehivesform.h \
    orderhistoryform.h \
    registerclientform.h \
    startwindow.h

FORMS +=

TRANSLATIONS += \
    BDD_en_AS.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
