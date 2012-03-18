#ifndef UTILS_H
#define UTILS_H
#include "OGRE/Ogre.h"

//using namespace Ogre;

class Utils{
public:
    static Ogre::Real getLengthBetweenPoints(Ogre::Vector3 a, Ogre::Vector3 b);
    static Ogre::Real getEdgeLength(Ogre::Entity * entity);
    static Ogre::Real getEdgeLength2D(Ogre::Entity * entity);
};
#endif // UTILS_H
