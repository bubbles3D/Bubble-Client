#include "OgreEngine/overlayUtils.h"

void OverlayUtils::setScaleKeepingCenter(Ogre::OverlayContainer * container, float height, float width){
     Ogre::Real oldHeight = container->getHeight();
     Ogre::Real oldWidth = container->getWidth();
     Ogre::Real oldLeft = container->getLeft();
     Ogre::Real oldTop = container->getTop();
     Ogre::GuiMetricsMode metricMode = container->getMetricsMode();

     switch(metricMode){
     case Ogre::GMM_PIXELS:
             container->setWidth(width);
             container->setHeight(height);
             container->setTop(oldTop + (oldHeight - height)/2);
             container->setLeft(oldLeft + (oldWidth - width)/2);
         break;
         default:
         break;
     }
 }
