#ifndef ORIENTEDOBJECT_H
#define ORIENTEDOBJECT_H

#include "object.h"
#include "environnement.h"

class OrientedObject : public Object
{
public:
    OrientedObject(Ogre::SceneManager * mSceneMgr);
    void setOrientation(Ogre::Vector3 directionToLookAt, side theSide = BOTTOM);

protected:
    Ogre::SceneNode* yawNode;
    Ogre::SceneNode* pitchNode;
};

#endif // ORIENTEDOBJECT_H
