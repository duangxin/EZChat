QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../shared/shared.pri)

SOURCES += \
    Controller/servercontroller.cpp \
    DataBase/database.cpp \
    Network/server.cpp \
    Network/tcpclientsocket.cpp \
    Network/tcpserver.cpp \
    main.cpp \
    mainwindow.cpp \
    Utilities/record.cpp

HEADERS += \
    Controller/servercontroller.h \
    DataBase/database.h \
    Network/server.h \
    Network/tcpclientsocket.h \
    Network/tcpserver.h \
    Utilities/stdDateTime.h \
    mainwindow.h \
    Utilities/record.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
