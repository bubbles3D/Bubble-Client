#ifndef BUBBLEOBJECT_H
#define BUBBLEOBJECT_H

#include "OGRE/Ogre.h"
#include "actor.h"
#include "orientedObject.h"
#include "objectUtils.h"

class BubbleObject : public OrientedObject
{
public:
    BubbleObject(Actor p, Ogre::SceneManager *mSceneMgr);
    void setBodyColor(float r, float g, float b);
    void updateState(Actor &p);

protected:
    //All node using in a bubble
    Ogre::SceneNode* leftEyesNode;
    Ogre::SceneNode* rightEyesNode;

    //bubble body's material
    Ogre::MaterialPtr bodyMaterial ;

    //bubble eyes' Material
    Ogre::MaterialPtr eyesMaterial ;

    //bubble body's color
    Ogre::ColourValue bodycolor;

};

#endif // BUBBLEOBJECT_H
