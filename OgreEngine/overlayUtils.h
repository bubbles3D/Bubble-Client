#ifndef OVERLAYUTILS_H
#define OVERLAYUTILS_H
#include <OGRE/Ogre.h>

class OverlayUtils{
public:
    /*
    * set the scale of the container to value keeping the center of the container
    * Note: currently it's only implemented for pixel mode when the panel is on the top right (cf alignment)
    * If it's not the case: do nothing
    */
    static void setScaleKeepingCenter(Ogre::OverlayContainer * container, float height, float width);
};

#endif // OVERLAYUTILS_H
