CONFIG   += console
CONFIG   -= app_bundle

SOURCES += \
    networkclient.cpp \
    player.cpp \
    app.cpp \
    model.cpp

HEADERS += \
    networkclient.h \
    player.h \
    model.h

 QT += \
    network \
    core

QT -= \
    gui

unix|win32: LIBS += -lqjson
