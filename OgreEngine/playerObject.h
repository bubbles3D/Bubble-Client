#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include "OGRE/Ogre.h"
#include "OgreEngine/bubbleObject.h"
#include "actor.h"
#include "OgreEngine/playerHUDManagement.h"
#include <OIS/OIS.h>

class PlayerObject : public BubbleObject
{
public:
    PlayerObject(Ogre::SceneManager *mSceneMgr,Player p);
    PlayerObject(QString id,side mside, Ogre::Vector3 position, Ogre::Vector3 directionToLookAt, Ogre::Vector3 size, Ogre::ColourValue color);
    Ogre::String getPlayerCameraName();
    Ogre::Vector3 getPlayerDirection();
    void updateState(Player &p);
    PlayerHUDManagement * getHUD();

    void mouseMouved(const OIS::MouseEvent &arg);
    virtual ~PlayerObject();


protected:
    Ogre::Camera* playerCamera;
    Ogre::SceneNode* targetNode;
    PlayerHUDManagement * hudMgt;
    float mRotateSpeed;
    enum side playerSide;

    void createPlayer(QString id);
};

#endif // PLAYEROBJECT_H
