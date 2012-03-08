#ifndef UTILS_H
#define UTILS_H
#include "OGRE/Ogre.h"

using namespace Ogre;

class Utils{
public:
    static Real getLengthBetweenPoints(Vector3 a, Vector3 b);
    static Real getEdgeLength(Ogre::Entity * entity);
};
#endif // UTILS_H
