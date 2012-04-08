#ifndef BUBBLEOBJECT_H
#define BUBBLEOBJECT_H

#include "OGRE/Ogre.h"
#include "actor.h"
#include "OgreEngine/orientedObject.h"
#include "OgreEngine/objectUtils.h"

class BubbleObject : public OrientedObject
{
public:
    BubbleObject(Ogre::SceneManager *mSceneMgr, Actor p);
    BubbleObject(Ogre::SceneManager *mSceneMgr, QString name, side mside, Ogre::Vector3 position, Ogre::Vector3 directionToLookAt, Ogre::Vector3 size, Ogre::ColourValue color );
    virtual ~BubbleObject();
    void setBodyColor(float r, float g, float b);
    virtual void updateState(Actor &p);

protected:
    //All node using in a bubble
    Ogre::SceneNode* leftEyesNode;
    Ogre::SceneNode* rightEyesNode;
    // The root entity node
    Ogre::SceneNode* entityNode;

    //entity
    Ogre::Entity* body;
    Ogre::Entity* leftEye;
    Ogre::Entity* rightEye;

    //bubble body's material
    Ogre::MaterialPtr bodyMaterial ;

    //bubble eyes' Material
    Ogre::MaterialPtr eyesMaterial ;

    //bubble body's color
    Ogre::ColourValue bodycolor;

    void initBubble(QString name,side mside, Ogre::Vector3 position, Ogre::Vector3 directionToLookAt, Ogre::Vector3 objectSize, Ogre::ColourValue color);
};

#endif // BUBBLEOBJECT_H
