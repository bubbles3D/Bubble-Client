#ifndef OBSTACLEOBJECT_H
#define OBSTACLEOBJECT_H

#include "OgreEngine/object.h"
#include "OGRE/Ogre.h"
#include "obstacles.h"

class ObstacleObject : public Object
{
public:
    ObstacleObject(Ogre::SceneManager * sceneMgr, Ogre::Vector3 size, QString id, Ogre::ColourValue color, Ogre::Vector3 position, Ogre::SceneNode * parentNode = 0);
    ObstacleObject(Ogre::SceneManager * sceneMgr, Obstacles p);
    virtual ~ObstacleObject();
    void updateState(Obstacles &p);
    Ogre::SceneNode * getNode();
    void setColor(float x, float y, float z);

protected:
    Ogre::MaterialPtr material;
    Ogre::Entity* entity;
    Ogre::ColourValue color;

    void initObstacle(QString id, Ogre::Vector3 position, Ogre::Vector3 objectSize, Ogre::ColourValue color);

};

#endif // OBSTACLEOBJECT_H
