#ifndef PLAYERHUDMANAGEMENT_H
#define PLAYERHUDMANAGEMENT_H
#include "OGRE/Ogre.h"
#include "overlayUtils.h"
#include <QString>

class PlayerHUDManagement{
public:
    PlayerHUDManagement(QString overlayLifeName, QString overlayLensName);
    void updateLife();
    void setLife(float lifeValue);

protected:
    Ogre::Overlay* lifeOverlay;
    Ogre::OverlayContainer * lifeContainer;
    Ogre::Overlay* lensOverlay;
    Ogre::OverlayContainer * lensContainer;
    float convertLifeToSize(float lifeValue);
};

#endif // PLAYERHUDMANAGEMENT_H
