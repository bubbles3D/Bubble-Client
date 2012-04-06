#include "bubbleObject.h"
#include <QDebug>

BubbleObject::BubbleObject(Ogre::SceneManager *mSceneMgr,Actor p ):
//Init scene manager
OrientedObject::OrientedObject(mSceneMgr,100, p.getId()) // 100 is the default size sphere
{
    qDebug()<<"Creating bubble";

    p.getColor(&(bodycolor.r),&(bodycolor.g),&(bodycolor.b));
    initBubble(p.getId(),(side) p.getCube(), Ogre::Vector3(p.getX(),p.getY(),p.getZ()), Ogre::Vector3(p.getVx(),p.getVy(),p.getVz()), Ogre::Vector3(p.getWidth(),p.getHeight(),p.getLength()),bodycolor);
}

BubbleObject::BubbleObject(Ogre::SceneManager *mSceneMgr, QString name, side mside, Ogre::Vector3 position, Ogre::Vector3 directionToLookAt, Ogre::Vector3 size, Ogre::ColourValue color ):
//Init scene manager
OrientedObject::OrientedObject(mSceneMgr,100,name) // 100 is the default size sphere
{
    qDebug()<<"Creating bubble";

    initBubble(name, mside, position, directionToLookAt, size,color);
    qDebug()<<"End Creating bubble";
}

void BubbleObject::initBubble(QString name,side mside, Ogre::Vector3 position, Ogre::Vector3 directionToLookAt, Ogre::Vector3 objectSize, Ogre::ColourValue color){
    qDebug()<<"init bubble";
    //Bubbles nodes creation
    entityNode = ((Ogre::SceneNode*)pitchNode)->createChildSceneNode(name.toStdString() + "_entity", Ogre::Vector3(0,0,0));
    leftEyesNode = ((Ogre::SceneNode*)entityNode)->createChildSceneNode(name.toStdString() +"_lEye", Ogre::Vector3(-15,15,39));
    rightEyesNode = ((Ogre::SceneNode*)entityNode)->createChildSceneNode(name.toStdString() +"_rEye", Ogre::Vector3(15,15,39));

    //Create entities
    Ogre::Entity* body = mSceneMgr->createEntity(name.toStdString() , "Prefab_Sphere");
    Ogre::Entity* leftEye = mSceneMgr->createEntity(name.toStdString() + "_lEye", "Prefab_Sphere");
    Ogre::Entity* rightEye = mSceneMgr->createEntity(name.toStdString() + "_rEye", "Prefab_Sphere");

    //Set eyes positions and scales
    leftEyesNode->scale(0.3,0.4,0.2);
    leftEyesNode->pitch(Ogre::Degree(-20));
    rightEyesNode->scale(0.3,0.4,0.2);
    rightEyesNode->pitch(Ogre::Degree(-20));

    //Set materials
    bodyMaterial = Ogre::MaterialManager::getSingleton().create(name.toStdString() +"_mat", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    bodyMaterial->setLightingEnabled(true);
    bodyMaterial->setDepthWriteEnabled(false);
    bodyMaterial->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    bodyMaterial->setDiffuse(Ogre::ColourValue(0,0,0,1));
    bodyMaterial->setSpecular(Ogre::ColourValue(0,0,0,0));
    bodyMaterial->setAmbient(Ogre::ColourValue(0,0,0,0));

    eyesMaterial = Ogre::MaterialManager::getSingleton().create(name.toStdString() +"_matEyes", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    eyesMaterial->setDiffuse(Ogre::ColourValue::Black);
    eyesMaterial->setAmbient(Ogre::ColourValue::Black);

    //Set bubble's color
    bodycolor = color;
    bodyMaterial->setSelfIllumination(bodycolor);

    //Link material
    body->setMaterial(bodyMaterial);
    leftEye->setMaterial(eyesMaterial);
    rightEye->setMaterial(eyesMaterial);

    //Attach entities
    ((Ogre::SceneNode*)entityNode)->attachObject(body);
    ((Ogre::SceneNode*)leftEyesNode)->attachObject(leftEye);
    ((Ogre::SceneNode*)rightEyesNode)->attachObject(rightEye);

    //Set state
    objectUtils::updateObjectState( node, pitchNode, yawNode, mside, position, directionToLookAt, objectSize, 100);
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

BubbleObject::~BubbleObject(){
    //No need to destroy node cf Object

    //But material need to be destroyed
    Ogre::MaterialManager::getSingleton().remove((Ogre::ResourcePtr&)bodyMaterial);
    Ogre::MaterialManager::getSingleton().remove((Ogre::ResourcePtr&)eyesMaterial);
}


