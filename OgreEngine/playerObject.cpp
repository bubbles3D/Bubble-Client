#include "playerObject.h"
#include <QString>


PlayerObject::PlayerObject(Ogre::SceneManager *mSceneMgr,Actor p):
BubbleObject(mSceneMgr,p)
{
    createPlayer(p.getId());
}

PlayerObject::PlayerObject(QString id,side mside, Ogre::Vector3 position, Ogre::Vector3 directionToLookAt, Ogre::Vector3 size, Ogre::ColourValue color):
    BubbleObject(mSceneMgr, id, mside, position, directionToLookAt, size, color )
{
    createPlayer(id);
}

void PlayerObject::createPlayer(QString id){
    //init camera
    playerCamera = mSceneMgr->createCamera(id.toStdString() + "_camera");
    mRotateSpeed = 0.15f;

    targetNode = pitchNode->createChildSceneNode(id.toStdString() + "_target", Ogre::Vector3(0,0,20));
    pitchNode->attachObject(playerCamera);
    entityNode->setVisible(false,true);
    playerCamera->rotate(Ogre::Vector3(0,1,0), Ogre::Angle(180));
}

Ogre::String PlayerObject::getPlayerCameraName(){
    return playerCamera->getName();
}

Ogre::Vector3 PlayerObject::getPlayerDirection(){
    return (targetNode->_getDerivedPosition() - node->_getDerivedPosition());//.x - node->_getDerivedPosition().x,targetNode->_getDerivedPosition().y - playerNode->_getDerivedPosition().y,playerTargetNode->_getDerivedPosition().z - playerNode->_getDerivedPosition().z)
}


void PlayerObject::mouseMouved(const OIS::MouseEvent &arg){


    yawNode->yaw(Ogre::Degree(-arg.state.X.rel * mRotateSpeed));
    pitchNode->needUpdate();
    Ogre::Vector3 verticalVect(pitchNode->getOrientation() * Ogre::Vector3::UNIT_Z);
    verticalVect.normalise();
    if( (arg.state.Y.rel < 0 && verticalVect.y > 0.9) || (arg.state.Y.rel > 0 && verticalVect.y < -0.9)){
        //Limit camera movement (looking up and down)
    }else{
        pitchNode->pitch(Ogre::Degree(+arg.state.Y.rel * mRotateSpeed));
    }
}

PlayerObject::~PlayerObject(){
    mSceneMgr->destroyCamera(playerCamera);
}
