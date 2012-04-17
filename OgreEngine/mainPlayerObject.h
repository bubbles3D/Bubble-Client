#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include "OGRE/Ogre.h"
#include "OgreEngine/bubbleObject.h"
#include "actor.h"
#include "OgreEngine/playerHUDManagement.h"
#include <OIS/OIS.h>

class MainPlayerObject : public BubbleObject
{
public:
    MainPlayerObject(Ogre::SceneManager *mSceneMgr,Player p);
    MainPlayerObject(QString id,side mside, Ogre::Vector3 position, Ogre::Vector3 directionToLookAt, Ogre::Vector3 size, Ogre::ColourValue color);
    Ogre::String getPlayerCameraName();
    Ogre::Vector3 getPlayerDirection();
    void updateState(Player &p);
    PlayerHUDManagement * getHUD();

    void mouseMouved(const OIS::MouseEvent &arg);
    virtual ~MainPlayerObject();


protected:
    Ogre::Camera* playerCamera;
    Ogre::SceneNode* targetNode;
    PlayerHUDManagement * hudMgt;
    float mRotateSpeed;
    enum side playerSide;

    void createPlayer(QString id);
};

#endif // PLAYEROBJECT_H
