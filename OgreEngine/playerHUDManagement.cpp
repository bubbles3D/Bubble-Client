#include "OgreEngine/playerHUDManagement.h"

float PlayerHUDManagement::alphaBlood = 0;
PlayerHUDManagement::PlayerHUDManagement(QString overlayLifeName, QString overlayLensName, QString overlayBloodName, float maxLifeValue, float maxLifeSize):
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

    //Initialize blood screen
    PlayerHUDManagement::alphaBlood = 0;
    bloodOverlay = Ogre::OverlayManager::getSingleton().getByName(overlayBloodName.toStdString());
    if(bloodOverlay){
         bloodContainer = bloodOverlay->getChild("blood");
         Ogre::MaterialPtr mat = bloodContainer->getMaterial();
         Ogre::Pass * pPass = mat->getTechnique(0)->getPass(0);
         pPass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
         pPass->setTransparentSortingEnabled(true);
         bloodTexture = pPass->getTextureUnitState(0);
    }else{
        //If we have not succed to retreive the life overlay
        bloodContainer = 0;
        bloodTexture = 0;
    }

}

void PlayerHUDManagement::updateHUD(float timeSinceLastFrame){

    updateLife(timeSinceLastFrame);
}

void PlayerHUDManagement::updateLife(float timeSinceLastFrame){
    if(PlayerHUDManagement::alphaBlood > 0){
        setAlphaBlood(PlayerHUDManagement::alphaBlood);
        PlayerHUDManagement::alphaBlood = PlayerHUDManagement::alphaBlood - PlayerHUDManagement::alphaBlood * timeSinceLastFrame * 0.5;
    }else{
       PlayerHUDManagement::alphaBlood = 0;
    }
}

void PlayerHUDManagement::setLife(float lifeValue){
    float lifeSize = convertLifeToSize(lifeValue);
    OverlayUtils::setScaleKeepingCenter(lifeContainer,lifeSize,lifeSize);
}

float PlayerHUDManagement::convertLifeToSize(float lifeValue){
    return maxLifeSize - (maxLife - lifeValue)/maxLife*maxLifeSize;
}

void PlayerHUDManagement::touched(){
    PlayerHUDManagement::alphaBlood = 1;
}

void PlayerHUDManagement::setAlphaBlood(float alpha){
    PlayerHUDManagement::alphaBlood = alpha;
    if(bloodOverlay){
         bloodOverlay->show();
           bloodTexture->setAlphaOperation(
            Ogre::LBX_MODULATE,
            Ogre::LBS_CURRENT,
            Ogre::LBS_MANUAL,
            alpha,alpha);
    }
}
