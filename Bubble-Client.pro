CONFIG   += console
CONFIG   -= app_bundle

SOURCES += \
    networkclient.cpp \
    player.cpp \
    app.cpp \
    model.cpp \
    gameapp.cpp

HEADERS += \
    networkclient.h \
    player.h \
    model.h \
    gameapp.h

 QT += \
    network \
    core

QT -= \
    gui

unix|win32: LIBS += -lqjson
