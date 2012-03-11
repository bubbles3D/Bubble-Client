CONFIG   += console
CONFIG   -= app_bundle

SOURCES += \
    networkclient.cpp \
    player.cpp \
    app.cpp \
    model.cpp \
    gameapp.cpp \
    actor.cpp \
    OgreEngine/TutorialApplication.cpp \
    OgreEngine/OgreApp.cpp \
    OgreEngine/BaseApplication.cpp \
    bullet.cpp \
    appdialog.cpp \
    OgreEngine/Utils.cpp \
    obstacles.cpp

HEADERS += \
    networkclient.h \
    player.h \
    model.h \
    gameapp.h \
    actor.h \
    /usr/include \
    /usr/include/OGRE \
    /usr/include/OGRE/Ogre.h \
    /usr/include/OIS \ 
    OgreEngine/TutorialApplication.h \
    OgreEngine/OgreApp.h \
    OgreEngine/BaseApplication.h \
    bullet.h \
    appdialog.h \
    OgreEngine/Utils.h \
    obstacles.h \
    /usr/local/include/CEGUI \
    /usr/local/include/CEGUI/CEGUI.h \
    /usr/local/include/CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h


LIBS += \
    -L/usr/lib \
    -L/usr/local/lib \
    -lOgreMain\
    -lOIS \
    -lCEGUIBase \
    -lCEGUIOgreRenderer

 QT += \
    network \
    core

unix|win32: LIBS += -lqjson

OTHER_FILES += \
    OgreEngine/data/samples.cfg \
    OgreEngine/data/resources.cfg \
    OgreEngine/data/plugins.cfg \
    OgreEngine/data/Textures/grass.jpg \
    OgreEngine/data/Textures/Eyes.xcf \
    OgreEngine/data/Textures/Eyes.png \
    OgreEngine/data/Textures/De.png \
    OgreEngine/data/Materials/Sphere.skeleton \
    OgreEngine/data/Materials/Sphere.mesh \
    OgreEngine/data/Materials/Plane.mesh \
    OgreEngine/data/Materials/MaterialBoxTest.material \
    OgreEngine/data/Materials/Material.material \
    OgreEngine/data/Materials/Grass.material \
    OgreEngine/data/Materials/cubi.mesh \
    OgreEngine/data/Materials/cubi.material \
    OgreEngine/data/Materials/BoxTest.mesh.xml \
    OgreEngine/data/Materials/BoxTest.mesh

FORMS += \
    appdialog.ui
