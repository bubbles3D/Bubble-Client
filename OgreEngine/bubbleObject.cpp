#include "bubbleObject.h"
#include <QDebug>

BubbleObject::BubbleObject(Ogre::SceneManager *mSceneMgr,Actor p ):
//Init scene manager
OrientedObject::OrientedObject(mSceneMgr,100, p.getId()), // 100 is the default size sphere
flag(0)
{
    qDebug()<<"Creating bubble";

    p.getColor(&(bodycolor.r),&(bodycolor.g),&(bodycolor.b));
    qDebug()<<"COLOR: "<<bodycolor.r<<" "<<bodycolor.g<<" "<<bodycolor.b;
    initBubble(p.getId(),(side) p.getCube(), Ogre::Vector3(p.getX(),p.getY(),p.getZ()), Ogre::Vector3(p.getVx(),p.getVy(),p.getVz()), Ogre::Vector3(p.getWidth(),p.getHeight(),p.getLength()),bodycolor);
}

BubbleObject::BubbleObject(Ogre::SceneManager *mSceneMgr, QString name, side mside, Ogre::Vector3 position, Ogre::Vector3 directionToLookAt, Ogre::Vector3 size, Ogre::ColourValue color ):
//Init scene manager
OrientedObject::OrientedObject(mSceneMgr,100,name), // 100 is the default size sphere
flag(0)
{
    qDebug()<<"Creating bubble";

    initBubble(name, mside, position, directionToLookAt, size,color);
    qDebug()<<"End Creating bubble";
}

void BubbleObject::initBubble(QString name,side mside, Ogre::Vector3 position, Ogre::Vector3 directionToLookAt, Ogre::Vector3 objectSize, Ogre::ColourValue color){
    qDebug()<<"init bubble id:"<<name;
    //Bubbles nodes creation
    entityNode = ((Ogre::SceneNode*)pitchNode)->createChildSceneNode(name.toStdString() + "_entity", Ogre::Vector3(0,0,0));
    leftEyesNode = ((Ogre::SceneNode*)entityNode)->createChildSceneNode(name.toStdString() +"_lEye", Ogre::Vector3(-15,15,39));
    rightEyesNode = ((Ogre::SceneNode*)entityNode)->createChildSceneNode(name.toStdString() +"_rEye", Ogre::Vector3(15,15,39));

    //Create entities
    body = mSceneMgr->createEntity(name.toStdString() , "Prefab_Sphere");
    leftEye = mSceneMgr->createEntity(name.toStdString() + "_lEye", "Prefab_Sphere");
    rightEye = mSceneMgr->createEntity(name.toStdString() + "_rEye", "Prefab_Sphere");

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
    setOrientation(directionToLookAt,mside);
    setPosition(position.x,position.y,position.z);
    setScale(objectSize);
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
    float r;
    float g;
    float b;
    p.getColor(&r,&g,&b);
    setBodyColor(r,g,b);

    setOrientation(Ogre::Vector3(p.getVx(),p.getVy(),p.getVz()),objectSide);

    setScale(Ogre::Vector3(p.getWidth(),p.getHeight(),p.getLength()));
    setPosition(p.getX(),p.getY(),p.getZ());
}

void BubbleObject::updateState(Player &p){
    updateState((Actor&) p);

}

//TO DELETE
void BubbleObject::updateFlag(bool){

    /*
    if(hasFlag == true){
        if (flag == 0){ //création du drapeau
            flag = new FlagObject(mSceneMgr,name + "FLAG");
            flag->attach(pitchNode);
        }
        flag->setPosition(0,scale.y/2,0);//On positionne le drapeau
    }else{
        if(flag != 0){//Destruction drapeau
            delete(flag);
            flag = 0;
        }
    }
    */
}

BubbleObject::~BubbleObject(){

    //But material need to be destroyed
    Ogre::MaterialManager::getSingleton().remove((Ogre::ResourcePtr&)bodyMaterial);
    Ogre::MaterialManager::getSingleton().remove((Ogre::ResourcePtr&)eyesMaterial);

    //and Entity too
    mSceneMgr->destroyEntity(body);
    mSceneMgr->destroyEntity(leftEye);
    mSceneMgr->destroyEntity(rightEye);

}

void BubbleObject::setScale(float scale){
    entityNode->setScale(scale/meshInitialSize,scale/meshInitialSize,scale/meshInitialSize);
    this->scale = Ogre::Vector3(scale,scale,scale);
    if(flag != 0){
        flag->setPosition(0,this->scale.y/2,0);
    }
}

void BubbleObject::setScale(Ogre::Vector3 scale){
    entityNode->setScale(scale.x/meshInitialSize,scale.y/meshInitialSize,scale.z/meshInitialSize);
    this->scale = scale;
    if(flag != 0){
        flag->setPosition(0,this->scale.y/2,0);
    }
}

Ogre::Vector3 BubbleObject::getScale(){
    return scale;
}

void BubbleObject::setFlag(FlagObject * flag){
    this->flag = flag;
    flag->setPosition(0,scale.y/2,0);
    flag->setOrientation(Ogre::Vector3(1,0,0),objectSide);

}

void BubbleObject::removeFlag(){
    this->flag = 0;
}

FlagObject * BubbleObject::getFlag(){
    return flag;
}


