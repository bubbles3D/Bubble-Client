SOURCES += \
    networkclient.cpp \
    player.cpp \
    Bubble-Client-OgrePart/TutorialApplication.cpp \
    Bubble-Client-OgrePart/BaseApplication.cpp \

HEADERS += \
    networkclient.h \
    player.h \
    Bubble-Client-OgrePart/TutorialApplication.h \
    Bubble-Client-OgrePart/BaseApplication.h \
    /usr/include \
    /usr/include/OGRE \
    /usr/include/OIS

LIBS += \
    -L usr/lib \
    -lOgreMain \
    -lOIS

 QT += \
    network

OTHER_FILES += \
    ../workspace/Bubble/Bubble-Client/samples.cfg \
    ../workspace/Bubble/Bubble-Client/resources.cfg \
    ../workspace/Bubble/Bubble-Client/plugins.cfg
