CONFIG   += console
CONFIG   -= app_bundle

SOURCES += \
    networkclient.cpp \
    player.cpp \
    app.cpp \
    model.cpp \
    gameapp.cpp \
    actor.cpp \
    OgreEngine/OgreApp.cpp \
    OgreEngine/BaseApplication.cpp \
    bullet.cpp \
    appdialog.cpp \
    obstacles.cpp \
    OgreEngine/entityUtils.cpp \
    OgreEngine/face.cpp \
    OgreEngine/cube.cpp \
    OgreEngine/overlayUtils.cpp \
    OgreEngine/playerHUDManagement.cpp \
    OgreEngine/bubbleObject.cpp \
    OgreEngine/playerObject.cpp \
    OgreEngine/object.cpp \
    OgreEngine/orientedObject.cpp \
    OgreEngine/bulletobject.cpp \
    OgreEngine/obstacleobject.cpp \
    OgreEngine/objectsManager.cpp \
    OgreEngine/flagObject.cpp

HEADERS += \
    networkclient.h \
    player.h \
    model.h \
    gameapp.h \
    actor.h \
    /usr/include \
    /usr/include/OGRE \
    /usr/include/OGRE/Ogre.h \
    /usr/include/OGRE/SdkCameraMan.h \
    /usr/include/OGRE/OgreMaterial.h \
    /usr/include/OGRE/OgreTextAreaOverlayElement.h \
    /usr/include/OIS \ 
    /usr/include/OIS/OIS.h \
    /usr/include/OIS/OISMouse.h \
    /usr/include/OIS/OISEvents.h \
    OgreEngine/OgreApp.h \
    OgreEngine/BaseApplication.h \
    bullet.h \
    appdialog.h \
    obstacles.h \
    OgreEngine/entityUtils.h \
    OgreEngine/face.h \
    OgreEngine/environnement.h \
    OgreEngine/cube.h \
    OgreEngine/overlayUtils.h \
    OgreEngine/playerHUDManagement.h \
    OgreEngine/bubbleObject.h \
    OgreEngine/playerObject.h \
    OgreEngine/object.h \
    OgreEngine/orientedObject.h \
    OgreEngine/bulletobject.h \
    OgreEngine/obstacleobject.h \
    OgreEngine/objectsManager.h \
    OgreEngine/flagObject.h



LIBS += \
    -L/usr/local/lib \
    -L/usr/lib \
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
