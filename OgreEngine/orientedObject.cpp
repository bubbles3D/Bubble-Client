#include "orientedObject.h"


OrientedObject::OrientedObject(Ogre::SceneManager * mSceneMgr, float size, QString name):
Object::Object(mSceneMgr, size, name )
{
    yawNode = ((Ogre::SceneNode*)node)->createChildSceneNode(name.toStdString() + "_yaw", Ogre::Vector3(0,0,0));
    pitchNode = ((Ogre::SceneNode*)yawNode)->createChildSceneNode(name.toStdString() + "_pitch", Ogre::Vector3(0,0,0));

}

void OrientedObject::setOrientation(Ogre::Vector3 directionToLookAt, side floor){

    if(directionToLookAt.isZeroLength()){
        //nothing to do
    }else{
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
}

OrientedObject::~OrientedObject(){
    //nothing to delete because Object do it for us
}
