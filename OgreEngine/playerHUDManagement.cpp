#include "OgreEngine/playerHUDManagement.h"

PlayerHUDManagement::PlayerHUDManagement(QString overlayLifeName, QString overlayLensName, float maxLifeValue, float maxLifeSize):
    maxLife(maxLifeValue), maxLifeSize(maxLifeSize)
{
    lifeOverlay = Ogre::OverlayManager::getSingleton().getByName(overlayLifeName.toStdString());
    if(lifeOverlay){
         lifeOverlay->show();
         lifeContainer = lifeOverlay->getChild("life");
    }else{
        //If we have not succed to retreive the life overlay
        lifeContainer = 0;
    }

    lensOverlay = Ogre::OverlayManager::getSingleton().getByName(overlayLensName.toStdString());
    if(lensOverlay){
         lensOverlay->show();
         lensContainer = lensOverlay->getChild("lens");
    }else{
        //If we have not succed to retreive the life overlay
        lensContainer = 0;
    }
  /*
    lensOverlay = Ogre::OverlayManager::getSingleton().getByName("FirstPerson/blood");
    if(lensOverlay){
         lensOverlay->show();
         lensContainer = lensOverlay->getChild("blood");

    }else{
        //If we have not succed to retreive the life overlay
        lensContainer = 0;
    }
    */
}

void PlayerHUDManagement::updateLife(){
//TODO
}

void PlayerHUDManagement::setLife(float lifeValue){
    float lifeSize = convertLifeToSize(lifeValue);
    OverlayUtils::setScaleKeepingCenter(lifeContainer,lifeSize,lifeSize);
}

float PlayerHUDManagement::convertLifeToSize(float lifeValue){
    return maxLifeSize - (maxLife - lifeValue)/maxLife*maxLifeSize;
}
