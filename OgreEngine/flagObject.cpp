#include "flagObject.h"

FlagObject::FlagObject(Ogre::SceneManager * mSceneMgr, float size, QString name, Ogre::ColourValue color):
OrientedObject(mSceneMgr, size, name)
{
    initFlag( mSceneMgr, name, color);
}
void FlagObject::initFlag(Ogre::SceneManager * mSceneMgr, QString name, Ogre::ColourValue color){


    //Bubbles nodes creation
    entityNode = ((Ogre::SceneNode*)pitchNode)->createChildSceneNode(name.toStdString() + "_entity", Ogre::Vector3(0,0,0));
    poleNode = ((Ogre::SceneNode*)entityNode)->createChildSceneNode(name.toStdString() +"_pole", Ogre::Vector3(0,50,0));
    canvasNode = ((Ogre::SceneNode*)entityNode)->createChildSceneNode(name.toStdString() +"_canvas", Ogre::Vector3(7,0.6,0));

    //Create entities
    pole = mSceneMgr->createEntity(name.toStdString() + "_pole", "mat.mesh");

    //create canvas
    canvas = new ObstacleObject(mSceneMgr,Ogre::Vector3(60,30,5), name + "_flag",Ogre::ColourValue(1,0,0,1),Ogre::Vector3(0,0,0),canvasNode);

    //Set scales positions and scales
    poleNode->setScale(5,50,5);

    //Set canvas's color
    canvasColor = color;
    canvas->setColor(canvasColor.r,canvasColor.g,canvasColor.b);

    //Attach entities
    ((Ogre::SceneNode*)poleNode)->attachObject(pole);

    //Set state TODO
    //setOrientation(directionToLookAt,mside);
    //setPosition(position.x,position.y,position.z);
    //setScale(objectSize);
}

FlagObject::~FlagObject(){


    //Entity need to be destroyed
    mSceneMgr->destroyEntity(pole);
    delete(canvas);
}

void FlagObject::setColor(float r, float g, float b){
    if(canvasColor.r != r || canvasColor.g != g || canvasColor.b != b){
        canvasColor.r = r;
        canvasColor.g = g;
        canvasColor.b = b;
        canvas->setColor(canvasColor.r,canvasColor.g,canvasColor.b);
    }
}
