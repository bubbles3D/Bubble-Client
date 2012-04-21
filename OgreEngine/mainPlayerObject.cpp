#include "mainPlayerObject.h"
#include <QString>


MainPlayerObject::MainPlayerObject(Ogre::SceneManager *mSceneMgr,Player p):
BubbleObject(mSceneMgr,p)
{
    createPlayer(p.getId());
}

MainPlayerObject::MainPlayerObject(QString id,side mside, Ogre::Vector3 position, Ogre::Vector3 directionToLookAt, Ogre::Vector3 size, Ogre::ColourValue color):
    BubbleObject(mSceneMgr, id, mside, position, directionToLookAt, size, color )
{
    createPlayer(id);
}

void MainPlayerObject::createPlayer(QString id){
    //init camera
    playerCamera = mSceneMgr->createCamera(id.toStdString() + "_camera");
    mRotateSpeed = 0.15f;

    targetNode = pitchNode->createChildSceneNode(id.toStdString() + "_target", Ogre::Vector3(0,0,20));
    pitchNode->attachObject(playerCamera);
    entityNode->setVisible(false,true);
    playerCamera->rotate(Ogre::Vector3(0,1,0), Ogre::Angle(180));

    //HUD
    hudMgt = new PlayerHUDManagement("FirstPerson/life", "FirstPerson/lens","FirstPerson/blood",40);
}

Ogre::String MainPlayerObject::getPlayerCameraName(){
    return playerCamera->getName();
}

Ogre::Vector3 MainPlayerObject::getPlayerDirection(){
    return (targetNode->_getDerivedPosition() - node->_getDerivedPosition());//.x - node->_getDerivedPosition().x,targetNode->_getDerivedPosition().y - playerNode->_getDerivedPosition().y,playerTargetNode->_getDerivedPosition().z - playerNode->_getDerivedPosition().z)
}


void MainPlayerObject::mouseMouved(const OIS::MouseEvent &arg){

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

PlayerHUDManagement* MainPlayerObject::getHUD(){
    return hudMgt;
}

void MainPlayerObject::updateState(Player &p){
    setBodyColor(p.r,p.g,p.b);
    // It's our player:

    //Set the player's main orientation according to the face of the cube

    switch(p.getCube()){
    //switch(plane){ //test
        case(BOTTOM):
            node->setOrientation(node->getInitialOrientation());
            break;
        case(ZSIDE_OP):
            node->setOrientation(node->getInitialOrientation());
            node->roll(Ogre::Degree(+90));
            break;
        case(TOP):
            node->setOrientation(node->getInitialOrientation());
            node->roll(Ogre::Degree(+180));
        break;
        case(ZSIDE):
            node->setOrientation(node->getInitialOrientation());
            node->roll(Ogre::Degree(-90));
            break;
        case(XSIDE_OP):
            node->setOrientation(node->getInitialOrientation());
            node->pitch(Ogre::Degree(-90));
            break;
        case(XSIDE):
            node->setOrientation(node->getInitialOrientation());
            node->pitch(Ogre::Degree(+90));
            break;
    }

    // Set our player's orientation on face switching
    if(playerSide != p.getCube()){ // if we change of cube's face
        Ogre::Vector3 directionToLookAt = targetNode->_getDerivedPosition() - node->_getDerivedPosition();
        setOrientation(directionToLookAt, (side) p.getCube());
        playerSide = (side) p.getCube();
    }

    //Set our player's position
    node->setPosition(p.getX(),p.getY(),p.getZ());
    entityNode->setScale(p.getLength()/100,p.getLength()/100,p.getLength()/100);

    //Update HUD
    hudMgt->setLife(p.getLife());
    hudMgt->setKillsValue(p.getKills());
    hudMgt->setDeathValue(p.getDeaths());

    //Update flag
    updateFlag(p.flag);
}

MainPlayerObject::~MainPlayerObject(){
    mSceneMgr->destroyCamera(playerCamera);
}