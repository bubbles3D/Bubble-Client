
#include "OgreEngine/entityUtils.h"
#include <QDebug>
//using namespace Ogre;

Ogre::Real entityUtils::getLengthBetweenPoints(Ogre::Vector3 a, Ogre::Vector3 b){
    return Ogre::Math::Sqrt((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y) + (b.z-a.z)*(b.z-a.z) );
}

Ogre::Real entityUtils::getEdgeLength(Ogre::Entity * entity){
    Ogre::Real min = -1;
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

Ogre::Real entityUtils::getEdgeLength2D(Ogre::Entity * entity){
    Ogre::Real min = -1;
    Ogre::Vector3 a = entity->getBoundingBox().getAllCorners()[0];
    qDebug()<<"A::"<<a.x<<" "<<a.y<<" "<<a.z;
    Ogre::Vector3 b= entity->getBoundingBox().getAllCorners()[2];
    qDebug()<<"B::"<<b.x<<" "<<b.y<<" "<<b.z;
    min = Ogre::Math::Sqrt((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y) + (b.z-a.z)*(b.z-a.z) );

    return min;
}

void entityUtils::initScale(Ogre::Entity* entity, Ogre::Node * node){
    Ogre::Real length = entityUtils::getEdgeLength(entity);
    Ogre::Real ratio = 4.98725/length;
    //Ogre::Real ratio = 1/length;

    qDebug()<<"RATIO";
    qDebug()<<ratio;
    qDebug()<<length;
    node->scale(ratio,ratio,ratio);

}



