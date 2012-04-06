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

PlayerObject::~PlayerObject(){
    mSceneMgr->destroyCamera(playerCamera);
}
