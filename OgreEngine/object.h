#ifndef OBJECT_H
#define OBJECT_H

#include "OGRE/Ogre.h"

class Object
{
public:
    Object(Ogre::SceneManager * sceneMgr, float initalSize = 1);
    void setPosition(float x, float y, float z);
    void setVisible(bool isVisible = true);
    void setScale(float scale);
protected:

    // The root node
    Ogre::SceneNode* node;

    // The root entity node
    Ogre::SceneNode* entityNode;
    float meshInitialSize;

    //SceneManager
    Ogre::SceneManager * mSceneMgr;
};

#endif // OBJECT_H
