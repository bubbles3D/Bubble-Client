#ifndef OVERLAYUTILS_H
#define OVERLAYUTILS_H
#include <OGRE/Ogre.h>
#include <QString>
#include <QDebug>

class OverlayUtils{
public:
    /*
    * set the scale of the container to value keeping the center of the container
    * Note: currently it's only implemented for pixel mode
    * If it's not the case: do nothing
    */
    static void setScaleKeepingCenter(Ogre::OverlayContainer * container, float height, float width);
    static void destroyAllOverlayContainerChildren(Ogre::OverlayContainer* node);
};

#endif // OVERLAYUTILS_H
