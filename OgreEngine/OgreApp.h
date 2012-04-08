#ifndef APP_H
#define APP_H

#include <QThread>
#include <QList>
#include <QPair>
#include <QString>
#include <QVariant>
#include <OGRE/Ogre.h>
//#include "OGRE/ExampleFrameListener.h"
#include <OIS/OIS.h>
#include "OGRE/Ogre.h"
#include "BaseApplication.h"
#include "model.h"
#include "OgreEngine/entityUtils.h"
#include "OgreEngine/cube.h"
#include "OgreEngine/playerHUDManagement.h"
#include "OgreEngine/bubbleObject.h"
#include "OgreEngine/playerObject.h"
#include "OgreEngine/bulletobject.h"
#include "OgreEngine/obstacleobject.h"
#include <stdlib.h>
#include <QMap>

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#endif

enum MODE {
    FIRST,FREE, MENU
};

class OgreApp : public BaseApplication, public QThread
{
public:
    OgreApp(void);
    ~OgreApp(void);
    void run();



protected:
    OgreBites::SdkCameraMan* playerCameraController;
    enum MODE mode;
    Cube * cubeScene;
    PlayerObject * player;
    QMap<QString,Object*> objects;

    //TEST
    enum side plane;

    virtual void createScene(void);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    virtual void createFrameListener(void);
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual void setupViewport(Ogre::SceneManager *curr,Ogre::String camera_Name);
    void updatePositions();
    void updatePlayersPositions();
    void updateBulletsState();
    void updateObstaclesStates();
    void destroyObjects(QList<QString> objectsToRemove);

};
#endif // APP_H

