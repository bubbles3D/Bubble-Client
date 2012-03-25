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
    obstacles.cpp \
    OgreEngine/objectUtils.cpp \
    OgreEngine/entityUtils.cpp \
    OgreEngine/face.cpp \
    OgreEngine/cube.cpp

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
    /usr/include/OIS \ 
    /usr/include/OIS/OIS.h \
    /usr/include/OIS/OISMouse.h \
    /usr/include/OIS/OISEvents.h \
    OgreEngine/TutorialApplication.h \
    OgreEngine/OgreApp.h \
    OgreEngine/BaseApplication.h \
    bullet.h \
    appdialog.h \
    obstacles.h \
    /usr/local/include/CEGUI \
    /usr/local/include/CEGUI/CEGUI.h \
    /usr/local/include/CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h \
    /usr/include/CEGUI \
    /usr/include/CEGUI/CEGUI.h \
    /usr/include/CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h \
    OgreEngine/objectUtils.h \
    OgreEngine/entityUtils.h \
    OgreEngine/face.h \
    OgreEngine/environnement.h \
    OgreEngine/cube.h



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
