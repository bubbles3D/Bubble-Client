
#include "OgreEngine/Utils.h"
#include <QDebug>
using namespace Ogre;

Real Utils::getLengthBetweenPoints(Vector3 a, Vector3 b){
    return Ogre::Math::Sqrt((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y) + (b.z-a.z)*(b.z-a.z) );
}

Real Utils::getEdgeLength(Ogre::Entity * entity){
    Real min = -1;
    Ogre::Vector3 a = entity->getBoundingBox().getAllCorners()[0];
    Ogre::Vector3 b= entity->getBoundingBox().getAllCorners()[1];
    min = Ogre::Math::Sqrt((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y) + (b.z-a.z)*(b.z-a.z) );
    for(int idx = 2; idx < 8 ;idx++){
        b = entity->getBoundingBox().getAllCorners()[idx];
        if(min > getLengthBetweenPoints(a,b)){
            min = getLengthBetweenPoints(a,b);
        }
    }
    return min;
}


