#ifndef BULLETOBJECT_H
#define BULLETOBJECT_H
#include "OgreEngine/object.h"
#include "OGRE/Ogre.h"
#include "bullet.h"

class BulletObject : public Object
{
public:
    BulletObject(Ogre::SceneManager * sceneMgr, float size, QString id, Ogre::ColourValue color, Ogre::Vector3 position);
    BulletObject(Ogre::SceneManager * sceneMgr, Bullet p);
    virtual ~BulletObject();
    void updateState(Bullet &p);
protected:
    Ogre::MaterialPtr material;
    Ogre::Entity* entity;
    Ogre::ColourValue color;

    void initBullet(QString id, Ogre::Vector3 position, float objectSize, Ogre::ColourValue color);
    void setColor(float x, float y, float z);
};

#endif // BULLETOBJECT_H
