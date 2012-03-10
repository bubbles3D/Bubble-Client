#ifndef APP_H
#define APP_H

#include <QThread>
#include <QList>
#include <QPair>
#include <QString>
#include <QVariant>
#include <OGRE/Ogre.h>
#include "OGRE/ExampleFrameListener.h"
#include <QString>
#include <stdio.h>
#include "OGRE/Ogre.h"
#include "BaseApplication.h"
#include "model.h"
#include "OgreEngine/Utils.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#endif

using namespace Ogre;

enum MODE {
    FIRST,FREE
};

class OgreApp : public BaseApplication, public QThread
{
public:
    OgreApp(void);
    ~OgreApp(void);
    void run();



protected:
    Ogre::Camera* playerCamera;
    Ogre::SceneNode* playerNode;
    Ogre::SceneNode* playerCameraNode;
    Ogre::SceneNode* playerTargetNode;
    enum MODE mode;


    float mRotateSpeed;

    virtual void createScene(void);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual void setupViewport(Ogre::SceneManager *curr,Ogre::String camera_Name);
    void updatePositions();
    void updatePlayersPositions();
    void updateObjectsPositions(const char * meshName, QList<Bullet> objectsList);
    void updateObjectsPositions(const char * meshName, QList<Obstacles> objectsList);
    void updateObjectPosition(Node* node,Node* cameraNode, Actor p);
    void updateObjectAnimation(Actor p, const char * animation);
    void updateObjectsAnimations(QList<Player> objectsList);
    void initScale(Ogre::Entity* entity, Ogre::Node * node);
    void removeObject(QString p);
    void removeObjects( QList<QString> names);

};
#endif // APP_H

