#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include "OGRE/Ogre.h"
#include "OgreEngine/bubbleObject.h"
#include "actor.h"

class PlayerObject : BubbleObject
{
public:
    PlayerObject(Ogre::SceneManager *mSceneMgr,Actor p);
    PlayerObject(QString id,side mside, Ogre::Vector3 position, Ogre::Vector3 directionToLookAt, Ogre::Vector3 size, Ogre::ColourValue color);
    ~PlayerObject();


protected:
    Ogre::Camera* playerCamera;
    float mRotateSpeed;
    Ogre::SceneNode* targetNode;
    enum side playerSide;

    void createPlayer(QString id);
};

#endif // PLAYEROBJECT_H
