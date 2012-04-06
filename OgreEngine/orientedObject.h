#ifndef ORIENTEDOBJECT_H
#define ORIENTEDOBJECT_H

#include "OgreEngine/object.h"
#include "environnement.h"
#include <QString>

class OrientedObject : public Object
{
public:
    OrientedObject(Ogre::SceneManager * mSceneMgr, float size, QString name);
    ~OrientedObject();
    void setOrientation(Ogre::Vector3 directionToLookAt, side theSide = BOTTOM);

protected:
    Ogre::SceneNode* yawNode;
    Ogre::SceneNode* pitchNode;
};

#endif // ORIENTEDOBJECT_H
