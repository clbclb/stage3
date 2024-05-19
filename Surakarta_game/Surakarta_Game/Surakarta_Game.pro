QT       += gui

QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Client.cpp \
    Server.cpp \
    choose_dialog.cpp \
    clock.cpp \
    ctrlpanel.cpp \
    main.cpp \
    main_window.cpp \
    player_info.cpp \
    pvp_game.cpp \
    surakarta_reason.cpp \
    timecontrol.cpp \
    widget.cpp \
    networkdata.cpp \
    networkserver.cpp \
    networksocket.cpp

HEADERS += \
    Client.h \
    Server.h \
    choose_dialog.h \
    clock.h \
    ctrlpanel.h \
    main_window.h \
    player_info.h \
    pvp_game.h \
    surakarta_common.h \
    surakarta_piece.h \
    surakarta_reason.h \
    timecontrol.h \
    widget.h \
    networkdata.h \
    networkserver.h \
    networksocket.h

FORMS += \
    clock.ui \
    widget.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
