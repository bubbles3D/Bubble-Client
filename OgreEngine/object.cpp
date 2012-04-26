#include "object.h"

Object::Object(Ogre::SceneManager * sceneMgr, float size, QString name, Ogre::SceneNode * parent )
{

    mSceneMgr = sceneMgr;

    if(parent == 0){
        this->parent =  mSceneMgr->getRootSceneNode();
    }else{
        this->parent = parent;
    }
    node = this->parent->createChildSceneNode(name.toStdString());

    this->name = name;

    //Object size
    meshInitialSize = size;

    scale = Ogre::Vector3(meshInitialSize,meshInitialSize,meshInitialSize);

}

Ogre::SceneNode * Object::getNode(){
    return node;
}

void Object::setPosition(float x, float y, float z){
    node->setPosition(x,y,z);
}

void Object::setVisible(bool isVisible){
     node->setVisible(isVisible,true);
}

void Object::setScale(float scale){
    node->setScale(scale/meshInitialSize,scale/meshInitialSize,scale/meshInitialSize);
    this->scale =  Ogre::Vector3(scale,scale,scale);

}

void Object::setScale(Ogre::Vector3 scale){
    node->setScale(scale.x/meshInitialSize,scale.y/meshInitialSize,scale.z/meshInitialSize);
    this->scale = scale;
}

void Object::attach(Ogre::SceneNode* nodeWhereAttach){
    //Detach node
    node->getParentSceneNode()->removeChild(node);

    //Attach
    nodeWhereAttach->addChild(node);
    //node->setPosition(0,0,0);
}

Object::~Object(){
    node->removeAndDestroyAllChildren();
}

QString Object::getName(){
    return name;
}
