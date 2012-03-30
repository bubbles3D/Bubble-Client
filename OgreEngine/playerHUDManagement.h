#ifndef PLAYERHUDMANAGEMENT_H
#define PLAYERHUDMANAGEMENT_H
#include "OGRE/Ogre.h"
#include "overlayUtils.h"
#include <QString>

class PlayerHUDManagement{
public:
    PlayerHUDManagement(QString overlayLifeName, QString overlayLensName, QString overlayBloodName, float maxLifeValue = 40, float maxLifeSize = 200);
    void updateLife(float timeSinceLastFrame);
    void setLife(float lifeValue);

    // pop up the blood screen
    static void touched();
    void setAlphaBlood(float alpha);
    void updateHUD(float timeSinceLastFrame);


protected:
    static float alphaBlood;
    static PlayerHUDManagement * instance;
    Ogre::Overlay* lifeOverlay;
    Ogre::OverlayContainer * lifeContainer;
    Ogre::Overlay* lensOverlay;
    Ogre::OverlayContainer * lensContainer;
    Ogre::Overlay* bloodOverlay;
    Ogre::OverlayContainer * bloodContainer;
    Ogre::TextureUnitState * bloodTexture;
    float convertLifeToSize(float lifeValue);
    float maxLife;
    float maxLifeSize;


};

#endif // PLAYERHUDMANAGEMENT_H
