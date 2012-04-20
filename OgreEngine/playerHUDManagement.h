#ifndef PLAYERHUDMANAGEMENT_H
#define PLAYERHUDMANAGEMENT_H
#include "OGRE/Ogre.h"
#include "overlayUtils.h"
#include "model.h"
#include <QString>
#include <QList>
#include <string>

enum GAME_MODE {
    DM,TDM, CTF
};

class PlayerHUDManagement{
public:
    PlayerHUDManagement(QString overlayLifeName, QString overlayLensName, QString overlayBloodName, float maxLifeValue = 40, float maxLifeSize = 200);

    //Update life indicator
    void setLife(float lifeValue);

    // pop up the blood screen
    static void touched();

    void updateHUD(float timeSinceLastFrame);

    void setGameMode(GAME_MODE mode);

    //Update scores
    void setKillsValue(int nbKill);
    void setDeathValue(int nbDeath);

    void displayStats();
    void hideStats();
    bool statsAreVisible();


protected:
    static float alphaBlood;
    static PlayerHUDManagement * instance;

    //life
    Ogre::Overlay* lifeOverlay;
    Ogre::OverlayContainer * lifeContainer;

    //lens
    Ogre::Overlay* lensOverlay;

    //Blood flash
    Ogre::Overlay* bloodOverlay;
    Ogre::TextureUnitState * bloodTexture;

    //Score
    Ogre::Overlay* scoreOverlay;
    Ogre::OverlayContainer * killValueContainer;
    Ogre::OverlayContainer * deathValueContainer;

    //Stats
    Ogre::Overlay* statsOverlay;
    Ogre::OverlayElement * playerContainer;
    Ogre::OverlayContainer * statsPanel;
    Ogre::OverlayContainer * playersStats;

    //life
    Ogre::Overlay* timeOverlay;
    Ogre::OverlayElement * timeContainer;

    //flag FirstPerson/flag
    Ogre::Overlay* flagOverlay;
    Ogre::OverlayElement * flagContainer;

    GAME_MODE gameMode;

    float convertLifeToSize(float lifeValue);
    float maxLife;
    float maxLifeSize;

    void setAlphaBlood(float alpha);
    void updateBlood(float timeSinceLastFrame);
    void setLifeColor(Ogre::ColourValue lifeColor);
    void setTime(QString time);
};

#endif // PLAYERHUDMANAGEMENT_H
