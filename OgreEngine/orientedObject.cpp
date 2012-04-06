#include "orientedObject.h"
#include "objectUtils.h"


OrientedObject::OrientedObject(Ogre::SceneManager * mSceneMgr, float size, QString name):
Object::Object(mSceneMgr, size, name )
{
    yawNode = ((Ogre::SceneNode*)node)->createChildSceneNode(name.toStdString() + "_yaw", Ogre::Vector3(0,0,0));
    pitchNode = ((Ogre::SceneNode*)yawNode)->createChildSceneNode(name.toStdString() + "_pitch", Ogre::Vector3(0,0,0));

}

void OrientedObject::setOrientation(Ogre::Vector3 directionToLookAt, side theSide){
    if(directionToLookAt.isZeroLength()){
        //If there is no direction to look
    }else{
       objectUtils::orientObjectToDirection((Ogre::SceneNode *)node,(Ogre::SceneNode *)yawNode,(Ogre::SceneNode *)pitchNode,theSide,directionToLookAt);
    }
}

OrientedObject::~OrientedObject(){
    //nothing to delete because Object do it for us
}
