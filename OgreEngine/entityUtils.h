#ifndef UTILS_H
#define UTILS_H
#include "OGRE/Ogre.h"

using namespace Ogre;

class entityUtils{
public:
    static Real getLengthBetweenPoints(Vector3 a, Vector3 b);
    static Real getEdgeLength(Ogre::Entity * entity);
    static Real getEdgeLength2D(Ogre::Entity * entity);
    static void initScale(Ogre::Entity* entity, Ogre::Node * node);
};
#endif // UTILS_H
