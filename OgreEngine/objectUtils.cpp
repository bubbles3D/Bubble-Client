#include "OgreEngine/objectUtils.h"
#include <QDebug>
//using namespace Ogre;

void objectUtils::updateObjectState(Ogre::SceneNode* node, Ogre::SceneNode* pitchNode, Ogre::SceneNode* yawNode, Actor p){
    //We update object's positions
    node->setPosition(p.getX(),p.getY(),p.getZ());
    //We update object's orientation
    Ogre::Vector3 directionToLookAt = Ogre::Vector3(p.getVx(), p.getVy(), p.getVz());

    if(directionToLookAt.isZeroLength()){
        //If there is no direction to look
    }else{
       objectUtils::orientPlayerToDirection((Ogre::SceneNode *)node,(Ogre::SceneNode *)yawNode,(Ogre::SceneNode *)pitchNode,(side)p.getCube(),directionToLookAt);
    }

    //Scale
    node->setScale(p.getWidth(),p.getHeight(),p.getLength());
}

void objectUtils::removeObject(QString name, Ogre::SceneManager* mSceneMgr){

        Ogre::Entity * entity;
        Ogre::SceneNode * node;
        try{
            qDebug()<<"Start REMOVING NODE";
            entity = mSceneMgr->getEntity(name.toStdString());
            node = (Ogre::SceneNode *) mSceneMgr->getRootSceneNode()->getChild(name.toStdString());
            node->removeAndDestroyAllChildren();
            mSceneMgr->destroyEntity(entity->getName());
            qDebug()<<"End REMOVING NODE";

        }catch (Ogre::Exception ex){
          qDebug()<<"ERROR REMOVING NODE";
        }
}

void objectUtils::orientPlayerToDirection(Ogre::SceneNode * node, Ogre::SceneNode * yawNode, Ogre::SceneNode * pitchNode, side floor, Ogre::Vector3 directionToLookAt){

    //Vectors representing directions to look at
    Ogre::Vector3 directionToLookAtHorizontal;
    Ogre::Vector3 directionToLookAtVertical;

    //Vectors representing the current direction
    Ogre::Vector3 srcHorizontal;
    Ogre::Vector3 srcVertical;

    // Get current orientation
    srcHorizontal = yawNode->getOrientation()* Ogre::Vector3::UNIT_Z;
    srcHorizontal.y = 0;
    srcHorizontal.normalise();

    srcVertical = pitchNode->getOrientation()* Ogre::Vector3::UNIT_Z;
    srcVertical.x = 0;
    srcVertical.normalise();

    // reset node orientation (Bottom)
    node->setOrientation(node->getInitialOrientation());

    directionToLookAtHorizontal.y = 0;
    directionToLookAtVertical.x = 0;

    //switch(p.getCube()){
    switch(floor){
    case BOTTOM: //bas

        directionToLookAtHorizontal.x = directionToLookAt.x;
        directionToLookAtHorizontal.z = directionToLookAt.z;

        directionToLookAtVertical.z = Ogre::Math::Sqrt(directionToLookAt.z * directionToLookAt.z + directionToLookAt.x * directionToLookAt.x) ;
        directionToLookAtVertical.y = directionToLookAt.y;

        break;
    case XSIDE_OP: //COTE X  OPP
        node->pitch(Ogre::Degree(-90));

        directionToLookAtHorizontal.x = directionToLookAt.x;
        directionToLookAtHorizontal.z = directionToLookAt.y;

        directionToLookAtVertical.z = Ogre::Math::Sqrt(directionToLookAt.y * directionToLookAt.y + directionToLookAt.x * directionToLookAt.x) ;
        directionToLookAtVertical.y = -directionToLookAt.z;

        break;
    case XSIDE: //COTE X
        node->pitch(Ogre::Degree(90));

        directionToLookAtHorizontal.x = directionToLookAt.x;
        directionToLookAtHorizontal.z = -directionToLookAt.y;

        directionToLookAtVertical.z = Ogre::Math::Sqrt(directionToLookAt.y * directionToLookAt.y + directionToLookAt.x * directionToLookAt.x) ;
        directionToLookAtVertical.y = directionToLookAt.z;

        break;
    case ZSIDE: //COTE Z

        node->roll(Ogre::Degree(-90));
        directionToLookAtHorizontal.x = -directionToLookAt.y;
        directionToLookAtHorizontal.z = directionToLookAt.z;

        directionToLookAtVertical.z = Ogre::Math::Sqrt(directionToLookAt.y * directionToLookAt.y + directionToLookAt.z * directionToLookAt.z) ;
        directionToLookAtVertical.y = directionToLookAt.x;

        break;
    case ZSIDE_OP:

        node->roll(Ogre::Degree(90));

        directionToLookAtHorizontal.x = directionToLookAt.y;
        directionToLookAtHorizontal.z = directionToLookAt.z;

        directionToLookAtVertical.z = Ogre::Math::Sqrt(directionToLookAt.z * directionToLookAt.z + directionToLookAt.y * directionToLookAt.y) ;
        directionToLookAtVertical.y = -directionToLookAt.x;

        break;
    case TOP:

        node->roll(Ogre::Degree(180));

        directionToLookAtHorizontal.x = -directionToLookAt.x;
        directionToLookAtHorizontal.z = directionToLookAt.z;

        directionToLookAtVertical.z = Ogre::Math::Sqrt(directionToLookAt.z * directionToLookAt.z + directionToLookAt.x * directionToLookAt.x) ;
        directionToLookAtVertical.y = -directionToLookAt.y;

        break;
    }

    // Normalise
    directionToLookAtHorizontal.normalise();
    directionToLookAtVertical.normalise();

    //Rotation laterale
    if ((1.0f + srcHorizontal.dotProduct(directionToLookAtHorizontal)) < 0.0001f)
    {
     yawNode->yaw(Ogre::Degree(180));
    }
    else
    {
     Ogre::Quaternion quat = srcHorizontal.getRotationTo(directionToLookAtHorizontal, Ogre::Vector3::UNIT_Y);
     yawNode->yaw(quat.getYaw());
    }
    //Rotation verticale
    if ((1.0f + srcVertical.dotProduct(directionToLookAtVertical)) < 0.0001f)
    {
     pitchNode->pitch(Ogre::Degree(180));
    }
    else
    {
     Ogre::Quaternion quat = srcVertical.getRotationTo(directionToLookAtVertical, Ogre::Vector3::UNIT_X);
     pitchNode->pitch(quat.getPitch());
    }

}

void objectUtils::updateObjectAnimation(Actor p, const char * animation, Ogre::SceneManager * sceneMgr ){
    Ogre::AnimationState *animationState;
    try{
        qDebug()<<"Ogre EXception not append 1 :: ::--------------------------------------------" ;
        Ogre::Entity* entity = sceneMgr->getEntity(p.getId().toStdString());
        qDebug()<<"Ogre EXception not append 2  ::- ::--------------------------------------------" ;
        animationState = entity->getAnimationState(animation);
        qDebug()<<"Ogre EXception not append 3  ::- ::--------------------------------------------" ;
        if (animationState->getEnabled() == false){
           animationState->setLoop(true);
           animationState->setEnabled(true);
        }
        animationState->addTime(0.05);

    }catch(Ogre::Exception ex){
        qDebug()<<"Ogre EXception animation ::--------------------------------------------" ;
    }

}

void objectUtils::removeObjects(QList<QString> names, Ogre::SceneManager * sceneMgr){
    //qDebug()<<names;
    foreach(QString name, names){
        objectUtils::removeObject(name,sceneMgr);
    }
}

void objectUtils::updateObjectsAnimations(QList<Player> objectsList, Ogre::SceneManager * sceneMgr){
qDebug()<<"Ogre EXception animation -1::--------------------------------------------" ;
     //Update elements position
     foreach(Actor p, objectsList){
         qDebug()<<"Ogre EXception animation -0::--------------------------------------------" ;
         objectUtils::updateObjectAnimation(p,"my_animation", sceneMgr);
     }
 }

void objectUtils::updateObjectsStates(const char * meshName, QList<Bullet> objectsList, Ogre::SceneManager * sceneManager){

    //Update elements position
    foreach(Actor p, objectsList){

        Ogre::Node* node;
        Ogre::Node* pitchNode;
        Ogre::Node* yawNode;
        Ogre::Node* entityNode;
        try{
            //Get object's nodes if they already exist
            node = sceneManager->getRootSceneNode()->getChild(p.getId().toStdString());
            yawNode = node->getChild(p.getId().toStdString()+"_rot");
            pitchNode = yawNode->getChild(p.getId().toStdString()+"_cam");
            entityNode = pitchNode->getChild(p.getId().toStdString()+"_entity");

        }catch (Ogre::Exception ex){
            //If the object doesn't already exist we create it
            Ogre::Entity* cube = sceneManager->createEntity(p.getId().toStdString(), meshName);
            node = sceneManager->getRootSceneNode()->createChildSceneNode(p.getId().toStdString());
            node->setPosition(p.getX(),p.getY(),p.getZ());
            //float ratio = p.getRatio();
            //node->scale(p.getWidth(),p.getHeight(),p.getLength());
            yawNode = ((Ogre::SceneNode*)node)->createChildSceneNode(p.getId().toStdString() + "_rot", Ogre::Vector3(0,0,0));
            pitchNode = ((Ogre::SceneNode*)yawNode)->createChildSceneNode(p.getId().toStdString() + "_cam", Ogre::Vector3(0,0,0));
            entityNode = ((Ogre::SceneNode*)pitchNode)->createChildSceneNode(p.getId().toStdString() + "_entity", Ogre::Vector3(0,0,0));
            ((Ogre::SceneNode*)entityNode)->attachObject(cube);
            //entityUtils::initScale(cube,node);
        }
        objectUtils::updateObjectState((Ogre::SceneNode*)node,(Ogre::SceneNode*)pitchNode,(Ogre::SceneNode*)yawNode,p);
    }
}

void objectUtils::updateObjectsStates(const char * meshName, QList<Obstacles> objectsList, Ogre::SceneManager * sceneManager){

    qDebug()<<"START MAP";
    //Update elements position
    foreach(Actor p, objectsList){

        qDebug()<<"NAME "<<p.getId();
        Ogre::Node* node;
        Ogre::Node* pitchNode;
        Ogre::Node* yawNode;
        Ogre::Node* entityNode;
        try{
            //Get object's nodes if they already exist
            node = sceneManager->getRootSceneNode()->getChild(p.getId().toStdString());
            yawNode = node->getChild(p.getId().toStdString()+"_rot");
            pitchNode = yawNode->getChild(p.getId().toStdString()+"_cam");
            entityNode = pitchNode->getChild(p.getId().toStdString()+"_entity");


        }catch (Ogre::Exception ex){
            //If the object doesn't already exist we create it
            Ogre::Entity* cube = sceneManager->createEntity(p.getId().toStdString(), meshName);
            node = sceneManager->getRootSceneNode()->createChildSceneNode(p.getId().toStdString());
            node->setPosition(p.getX(),p.getY(),p.getZ());
            //float ratio = p.getRatio();
            //node->scale(p.getWidth(),p.getHeight(),p.getLength());
            yawNode = ((Ogre::SceneNode*)node)->createChildSceneNode(p.getId().toStdString() + "_rot", Ogre::Vector3(0,0,0));
            pitchNode = ((Ogre::SceneNode*)yawNode)->createChildSceneNode(p.getId().toStdString() + "_cam", Ogre::Vector3(0,0,0));
            entityNode = ((Ogre::SceneNode*)pitchNode)->createChildSceneNode(p.getId().toStdString() + "_entity", Ogre::Vector3(0,0,0));
            ((Ogre::SceneNode*)entityNode)->attachObject(cube);
            entityUtils::initScale(cube,node);
        }

        objectUtils::updateObjectState((Ogre::SceneNode*)node,(Ogre::SceneNode*)pitchNode,(Ogre::SceneNode*)yawNode,p);

    }
    qDebug()<<"END MAP";
}

