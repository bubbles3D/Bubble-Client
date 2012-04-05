#include "orientedObject.h"
#include "objectUtils.h"


OrientedObject::OrientedObject(Ogre::SceneManager * mSceneMgr):
Object::Object(mSceneMgr)
{
}

void OrientedObject::setOrientation(Ogre::Vector3 directionToLookAt, side theSide){
    if(directionToLookAt.isZeroLength()){
        //If there is no direction to look
    }else{
       objectUtils::orientPlayerToDirection((Ogre::SceneNode *)node,(Ogre::SceneNode *)yawNode,(Ogre::SceneNode *)pitchNode,theSide,directionToLookAt);
    }
}
