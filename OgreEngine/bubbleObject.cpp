#include "bubbleObject.h"
#include <QDebug>

BubbleObject::BubbleObject(Actor p, Ogre::SceneManager *mSceneMgr):
//Init scene manager
OrientedObject::OrientedObject(mSceneMgr)
{
    qDebug()<<"Creating bubble";

    //Bubbles nodes creation
    node = mSceneMgr->getRootSceneNode()->createChildSceneNode(p.getId().toStdString());
    yawNode = ((Ogre::SceneNode*)node)->createChildSceneNode(p.getId().toStdString() + "_yaw", Ogre::Vector3(0,0,0));
    pitchNode = ((Ogre::SceneNode*)yawNode)->createChildSceneNode(p.getId().toStdString() + "_pitch", Ogre::Vector3(0,0,0));
    entityNode = ((Ogre::SceneNode*)pitchNode)->createChildSceneNode(p.getId().toStdString() + "_entity", Ogre::Vector3(0,0,0));
    leftEyesNode = ((Ogre::SceneNode*)entityNode)->createChildSceneNode(p.getId().toStdString() +"_lEye", Ogre::Vector3(-15,15,39));
    rightEyesNode = ((Ogre::SceneNode*)entityNode)->createChildSceneNode(p.getId().toStdString() +"_rEye", Ogre::Vector3(15,15,39));

    //Create entities
    Ogre::Entity* body = mSceneMgr->createEntity(p.getId().toStdString() , "Prefab_Sphere");
    Ogre::Entity* leftEye = mSceneMgr->createEntity(p.getId().toStdString() + "_lEye", "Prefab_Sphere");
    Ogre::Entity* rightEye = mSceneMgr->createEntity(p.getId().toStdString() + "_rEye", "Prefab_Sphere");

    meshInitialSize = 100; // prefab sphere size

    //Set eyes positions and scales
    leftEyesNode->scale(0.3,0.4,0.2);
    leftEyesNode->pitch(Ogre::Degree(-20));
    rightEyesNode->scale(0.3,0.4,0.2);
    rightEyesNode->pitch(Ogre::Degree(-20));

    //Set materials
    bodyMaterial = Ogre::MaterialManager::getSingleton().create(p.getId().toStdString() +"_mat", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    bodyMaterial->setLightingEnabled(true);
    bodyMaterial->setDepthWriteEnabled(false);
    bodyMaterial->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    bodyMaterial->setDiffuse(Ogre::ColourValue(0,0,0,1));
    bodyMaterial->setSpecular(Ogre::ColourValue(0,0,0,0));
    bodyMaterial->setAmbient(Ogre::ColourValue(0,0,0,0));

    eyesMaterial = Ogre::MaterialManager::getSingleton().create(p.getId().toStdString() +"_matEyes", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    eyesMaterial->setDiffuse(Ogre::ColourValue::Black);
    eyesMaterial->setAmbient(Ogre::ColourValue::Black);

    //Set bubble's color
    p.getColor(&(bodycolor.r),&(bodycolor.g),&(bodycolor.b));
    bodyMaterial->setSelfIllumination(bodycolor);

    //Link material
    body->setMaterial(bodyMaterial);
    leftEye->setMaterial(eyesMaterial);
    rightEye->setMaterial(eyesMaterial);

    //Attach entities
    ((Ogre::SceneNode*)entityNode)->attachObject(body);
    ((Ogre::SceneNode*)leftEyesNode)->attachObject(leftEye);
    ((Ogre::SceneNode*)rightEyesNode)->attachObject(rightEye);
}

void BubbleObject::setBodyColor(float r, float g, float b){
    if(bodycolor.r != r || bodycolor.g != g || bodycolor.b != b){
        bodycolor.r = r;
        bodycolor.g = g;
        bodycolor.b = b;
        bodyMaterial->setSelfIllumination(bodycolor);
    }
}

void BubbleObject::updateState(Actor &p){
    setBodyColor(p.r,p.g,p.b);
    objectUtils::updateObjectState(node, pitchNode, yawNode, p, 100);
}
