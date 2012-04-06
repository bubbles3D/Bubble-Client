#include "object.h"

Object::Object(Ogre::SceneManager * sceneMgr, float size, QString name )
{
    mSceneMgr = sceneMgr;

    // The root node
    node = mSceneMgr->getRootSceneNode()->createChildSceneNode(name.toStdString());

    //Object size
    meshInitialSize = size;
}

void Object::setPosition(float x, float y, float z){
    node->setPosition(x,y,z);
}

void Object::setVisible(bool isVisible){
     node->setVisible(isVisible,true);
}

void Object::setScale(float scale){
    node->setScale(scale/meshInitialSize,scale/meshInitialSize,scale/meshInitialSize);

}

Object::~Object(){
    node->removeAndDestroyAllChildren();
}
