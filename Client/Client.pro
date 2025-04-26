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
    Controller/clientcontroller_chat.cpp \
    Controller/clientcontroller_friends.cpp \
    Controller/clientcontroller_log_reg.cpp \
    Controller/clientcontroller_modify.cpp \
    GUI/addfriend.cpp \
    GUI/changeavatar.cpp \
    GUI/changename.cpp \
    GUI/deletefriend.cpp \
    GUI/frdmanege.cpp \
    GUI/login.cpp \
    GUI/register.cpp \
    GUI/tipbox.cpp \
    GUI/widget.cpp \
    Network/Handler/addfriendanswerhandler.cpp \
    Network/Handler/addfriendhandler.cpp \
    Network/Handler/changeavatarhandler.cpp \
    Network/Handler/changenamehandler.cpp \
    Network/Handler/chatmsghandler.cpp \
    Network/Handler/deletefriendhandler.cpp \
    Network/Handler/friendlisthandler.cpp \
    Network/Handler/loginhandler.cpp \
    Network/Handler/registerhandler.cpp \
    Network/Handler/syncmessageshandler.cpp \
    Network/clienthandlerreg.cpp \
    Network/tcpclientsocket.cpp \
    Utilities/encryption.cpp \
    database.cpp \
    Utilities/movewidgetevent.cpp \
    main.cpp


HEADERS += \
    Controller/clientcontroller.h \
    GUI/addfriend.h \
    GUI/changeavatar.h \
    GUI/changename.h \
    GUI/deletefriend.h \
    GUI/frdmanege.h \
    GUI/login.h \
    GUI/register.h \
    GUI/tipbox.h \
    GUI/widget.h \
    Network/Handler/MsgHandler.h \
    Network/Handler/addfriendanswerhandler.h \
    Network/Handler/addfriendhandler.h \
    Network/Handler/changeavatarhandler.h \
    Network/Handler/changenamehandler.h \
    Network/Handler/chatmsghandler.h \
    Network/Handler/deletefriendhandler.h \
    Network/Handler/friendlisthandler.h \
    Network/Handler/loginhandler.h \
    Network/Handler/registerhandler.h \
    Network/Handler/syncmessageshandler.h \
    Network/clienthandlerreg.h \
    Network/tcpclientsocket.h \
    Utilities/config.h \
    Utilities/encryption.h \
    Utilities/stdDateTime.h \
    database.h \
    Utilities/movewidgetevent.h



FORMS += \
    GUI/addfriend.ui \
    GUI/changeavatar.ui \
    GUI/changename.ui \
    GUI/deletefriend.ui \
    GUI/frdmanege.ui \
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




