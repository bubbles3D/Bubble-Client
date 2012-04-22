#ifndef FLAGOBJECT_H
#define FLAGOBJECT_H
#include "OgreEngine/orientedObject.h"
#include "OgreEngine/obstacleobject.h"
#include "flag.h"

class FlagObject: public OrientedObject{
public:
    FlagObject(Ogre::SceneManager * mSceneMgr, QString name, Ogre::ColourValue color = Ogre::ColourValue::Red);
    FlagObject(Ogre::SceneManager * mSceneMgr, Actor p);
    virtual ~FlagObject();
    void setColor(float r, float g, float b);
    void updateState(Flag &p);

protected:
    //All node used in a flag
    Ogre::SceneNode* canvasNode;
    Ogre::SceneNode* poleNode;

    // The root entity node
    Ogre::SceneNode* entityNode;

    //entity
    Ogre::Entity* pole;

    ObstacleObject* canvas;

    //flag canvas' color
    Ogre::ColourValue canvasColor;

    void initFlag(Ogre::SceneManager * mSceneMgr, QString name, Ogre::ColourValue color);
};

#endif // FLAGOBJECT_H
