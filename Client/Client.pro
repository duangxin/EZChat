QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../shared/shared.pri)

SOURCES += \
    Controller/clientcontroller.cpp \
    Controller/clientcontroller_log_reg.cpp \
    GUI/login.cpp \
    GUI/register.cpp \
    GUI/tipbox.cpp \
    GUI/widget.cpp \
    Network/tcpclientsocket.cpp \
    Utilities/encryption.cpp \
    database.cpp \
    Utilities/movewidgetevent.cpp \
    main.cpp


HEADERS += \
    Controller/clientcontroller.h \
    GUI/login.h \
    GUI/register.h \
    GUI/tipbox.h \
    GUI/widget.h \
    Network/tcpclientsocket.h \
    Utilities/encryption.h \
    database.h \
    Utilities/movewidgetevent.h



FORMS += \
    GUI/login.ui \
    GUI/register.ui \
    GUI/tipbox.ui \
    GUI/widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    GUI/resources.qrc




