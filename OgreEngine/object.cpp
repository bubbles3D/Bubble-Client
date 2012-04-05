#include "object.h"

Object::Object(Ogre::SceneManager * sceneMgr, float initialSize)
{
    mSceneMgr = sceneMgr;
    meshInitialSize = initialSize;
}

void Object::setPosition(float x, float y, float z){
    node->setPosition(x,y,z);
}

void Object::setVisible(bool isVisible){
     node->setVisible(isVisible,true);
}

void Object::setScale(float scale){
    entityNode->setScale(scale/meshInitialSize,scale/meshInitialSize,scale/meshInitialSize);// 100 is the default size of prefab sphere
}

