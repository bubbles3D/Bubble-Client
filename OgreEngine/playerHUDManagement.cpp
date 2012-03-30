#include "OgreEngine/playerHUDManagement.h"

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
    alphaBlood = 0;
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

    if(alphaBlood > 0){
        setAlphaBlood(alphaBlood);
        alphaBlood = alphaBlood - alphaBlood * timeSinceLastFrame * 0.5;
    }else{
       alphaBlood = 0;
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
    return maxLifeSize - (maxLife - lifeValue)/maxLife*maxLifeSize;
}

void PlayerHUDManagement::touched(){
    setAlphaBlood(1);
}

void PlayerHUDManagement::setAlphaBlood(float alpha){
    alphaBlood = alpha;
    if(bloodOverlay){
         bloodOverlay->show();
           bloodTexture->setAlphaOperation(
            Ogre::LBX_MODULATE,
            Ogre::LBS_CURRENT,
            Ogre::LBS_MANUAL,
            alpha,alpha);
    }
}
