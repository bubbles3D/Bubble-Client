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

void OverlayUtils::destroyAllOverlayContainerChildren(Ogre::OverlayContainer* node){//On 2 lvls
    //
    qDebug()<<"(a)";
    Ogre::OverlayContainer::ChildIterator ci = ((Ogre::OverlayContainer*)node)->getChildIterator();
    while (ci.hasMoreElements())
    {
        Ogre::OverlayElement* child = ci.getNext();
        qDebug()<<"(b)";
            QString b = QString(((std::string)(child->getName())).c_str());
            qDebug()<<"ttt"<<(b);
            ((Ogre::OverlayContainer*)node)->removeChild(child->getName());

            Ogre::OverlayContainer::ChildIterator cic = ((Ogre::OverlayContainer*)child)->getChildIterator();
            while (cic.hasMoreElements())
            {
                Ogre::OverlayElement* lastChild = cic.getNext();
                QString a = QString(((std::string)(lastChild->getName())).c_str());
                qDebug()<<a;
                Ogre::OverlayManager::getSingleton().destroyOverlayElement(lastChild->getName());
            }

            Ogre::OverlayManager::getSingleton().destroyOverlayElement(child);
    }
}
