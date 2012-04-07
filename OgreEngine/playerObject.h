#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include "OGRE/Ogre.h"
#include "OgreEngine/bubbleObject.h"
#include "actor.h"
#include <OIS/OIS.h>

class PlayerObject : BubbleObject
{
public:
    PlayerObject(Ogre::SceneManager *mSceneMgr,Actor p);
    PlayerObject(QString id,side mside, Ogre::Vector3 position, Ogre::Vector3 directionToLookAt, Ogre::Vector3 size, Ogre::ColourValue color);
    Ogre::String getPlayerCameraName();
    Ogre::Vector3 getPlayerDirection();

    void mouseMouved(const OIS::MouseEvent &arg);
    ~PlayerObject();


protected:
    Ogre::Camera* playerCamera;
    float mRotateSpeed;
    Ogre::SceneNode* targetNode;
    enum side playerSide;

    void createPlayer(QString id);
};

#endif // PLAYEROBJECT_H
