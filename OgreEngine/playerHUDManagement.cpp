#include "OgreEngine/playerHUDManagement.h"

PlayerHUDManagement::PlayerHUDManagement(QString overlayLifeName, QString overlayLensName){
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
         lensContainer = lensOverlay->getChild("life");
    }else{
        //If we have not succed to retreive the life overlay
        lensContainer = 0;
    }
}

void PlayerHUDManagement::updateLife(){
//TODO
}

void PlayerHUDManagement::setLife(float lifeValue){
    float lifeSize = convertLifeToSize(lifeValue);
    OverlayUtils::setScaleKeepingCenter(lifeContainer,lifeSize,lifeSize);
}

float PlayerHUDManagement::convertLifeToSize(float lifeValue){
    return 100 - (20 - lifeValue)/20*100;
}
