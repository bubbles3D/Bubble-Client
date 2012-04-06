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
#include "OgreEngine/objectUtils.h"
#include "OgreEngine/cube.h"
#include "OgreEngine/playerHUDManagement.h"
#include "OgreEngine/bubbleObject.h"
#include <stdlib.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#endif

//using namespace Ogre;

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
    Ogre::Camera* playerCamera;
    OgreBites::SdkCameraMan* playerCameraController;
    Ogre::SceneNode* playerNode;
    Ogre::SceneNode* playerYawNode;
    Ogre::SceneNode* playerPitchNode;
    Ogre::SceneNode* playerTargetNode;
    Ogre::SceneNode* playerEntityNode;
    Ogre::SceneNode* playerLifeNode;
    enum side playerSide;
    enum MODE mode;
    Cube * cubeScene;
    PlayerHUDManagement * playerHUDMgt;

    //TEST
    enum side plane;

    float mRotateSpeed;

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

};
#endif // APP_H

