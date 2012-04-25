#ifndef ORIENTEDOBJECT_H
#define ORIENTEDOBJECT_H

#include "OgreEngine/object.h"
#include "environnement.h"
#include <QString>

class OrientedObject : public Object
{
public:
    OrientedObject(Ogre::SceneManager * mSceneMgr, float size, QString name);
    virtual ~OrientedObject();
    void setOrientation(Ogre::Vector3 directionToLookAt, side theSide = BOTTOM);
    //void orientObjectToDirection(Ogre::SceneNode * playerNode, Ogre::SceneNode * yawNode, Ogre::SceneNode * pitchNode, side floor, Ogre::Vector3 directionToLookAt);
    Ogre::SceneNode * getPitchNode();
protected:
    Ogre::SceneNode* yawNode;
    Ogre::SceneNode* pitchNode;

    side objectSide;
};

#endif // ORIENTEDOBJECT_H
