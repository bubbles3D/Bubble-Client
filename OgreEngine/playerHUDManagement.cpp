#include "OgreEngine/playerHUDManagement.h"
#include <QDebug>
#include <OGRE/OgreTextAreaOverlayElement.h>

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
    }else{
        //If we have not succed to retreive the life overlay
    }

    //Initialize blood screen
    PlayerHUDManagement::alphaBlood = 0;
    bloodOverlay = Ogre::OverlayManager::getSingleton().getByName(overlayBloodName.toStdString());
    if(bloodOverlay){
         Ogre::MaterialPtr mat = bloodOverlay->getChild("blood")->getMaterial();
         Ogre::Pass * pPass = mat->getTechnique(0)->getPass(0);
         pPass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
         pPass->setTransparentSortingEnabled(true);
         bloodTexture = pPass->getTextureUnitState(0);
    }else{
        //If we have not succed to retreive the life overlay
        bloodTexture = 0;
    }

    //Score
    scoreOverlay = Ogre::OverlayManager::getSingleton().getByName("FirstPerson/score");
    //qDebug()<<"SCORE: "<<(int)scoreOverlay;
    if(scoreOverlay){
        scoreOverlay->show();
        killValueContainer = scoreOverlay->getChild("killValue");
        deathValueContainer = scoreOverlay->getChild("deathValue");
    }else{
        //If we have not succed to retreive the life overlay
        killValueContainer = 0;
        deathValueContainer = 0;
        qDebug()<<"ERROR";
    }

    //Stats
    statsOverlay = Ogre::OverlayManager::getSingleton().getByName("Stats/stats");
    if(statsOverlay){
        statsPanel = statsOverlay->getChild("statsPanel");
        //playersNamesContainer = statsOverlay->getChild("statsPanel")->getChild("playersNames");
       // playersKillsContainer = statsOverlay->getChild("statsPanel")->getChild("playersKills");
       // playersDeathsContainer = statsOverlay->getChild("statsPanel")->getChild("playersDeaths");
        playersStats = (Ogre::OverlayContainer*) statsPanel->getChild("playersStats");
        playerContainer = playersStats->getChild("playerStat");
        playerContainer->hide();

    }else{
        //If we have not succed to retreive the life overlay
        playersStats = 0;
        playerContainer = 0;
        qDebug()<<"ERROR";
    }


    /*
//Dynamic creation example
    Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();

    // Create a panel
          Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(
             overlayManager.createOverlayElement("Panel", "PanelName"));
          panel->setMetricsMode(Ogre::GMM_PIXELS);
          panel->setPosition(10, 10);
          panel->setDimensions(100, 100);

    // Create a text area
          Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*>(
             overlayManager.createOverlayElement("TextArea", "TextAreaName"));
          textArea->setMetricsMode(Ogre::GMM_PIXELS);
          textArea->setPosition(100, 100);
          textArea->setDimensions(100, 100);
          textArea->setCharHeight(16);
          // set the font name to the font resource that you just created.
          textArea->setFontName("StarWars");//StarWars
          // say something
          textArea->setCaption("0 Celllo ff \n blaaaa");

          // Add the text area to the panel
            panel->addChild(textArea);
            // Create an overlay, and add the panel
            Ogre::Overlay* overlay = overlayManager.create("OverlayName");
            overlay->add2D(panel);
            // Show the overlay
            overlay->show();
*/
}

void PlayerHUDManagement::updateHUD(float timeSinceLastFrame){

    updateBlood(timeSinceLastFrame);
}

void PlayerHUDManagement::updateBlood(float timeSinceLastFrame){
    if(PlayerHUDManagement::alphaBlood > 0){
        setAlphaBlood(PlayerHUDManagement::alphaBlood);
        PlayerHUDManagement::alphaBlood = PlayerHUDManagement::alphaBlood - PlayerHUDManagement::alphaBlood * timeSinceLastFrame;
    }else{
       PlayerHUDManagement::alphaBlood = 0;
    }
}

void PlayerHUDManagement::setLife(float lifeValue){
    float lifeSize = convertLifeToSize(lifeValue);
    OverlayUtils::setScaleKeepingCenter(lifeContainer,lifeSize,lifeSize);

    if(lifeValue == 1){
        setLifeColor(Ogre::ColourValue::Red);
    }else{
        setLifeColor(Ogre::ColourValue::White);
    }
}

void PlayerHUDManagement::setLifeColor(Ogre::ColourValue lifeColor){
    Ogre::TextureUnitState * lifeTex = lifeContainer->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0);
    lifeTex->setColourOperationEx(Ogre::LBX_MODULATE,Ogre::LBS_TEXTURE,Ogre::LBS_MANUAL,Ogre::ColourValue::White,lifeColor);
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

void PlayerHUDManagement::setKillsValue(int nbKill){
    killValueContainer->setCaption(Ogre::StringConverter::toString(nbKill));
}
void PlayerHUDManagement::setDeathValue(int nbDeath){
    deathValueContainer->setCaption(Ogre::StringConverter::toString(nbDeath));
}

void PlayerHUDManagement::displayStats(){

    //Clean old stats (to move in a new methode)
    Ogre::OverlayContainer::ChildIterator ci = ((Ogre::OverlayContainer*)playersStats)->getChildIterator();
    while (ci.hasMoreElements())
    {
        Ogre::OverlayElement* child = ci.getNext();
        if((child->getName()).c_str() != playerContainer->getName()){
            QString a = QString(((std::string)(child->getName())).c_str());
            qDebug()<<(a);
            ((Ogre::OverlayContainer*)playersStats)->removeChild(child->getName());

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

    Model * mod = Model::getInstance();
    QList<Player> players(mod->getAllPlayers());
    int position = 0;
    foreach(Player p, players){
        QString kills = QString::number(p.getKills()) ;

        // Create a player panel
        Ogre::OverlayElement* panel= playerContainer->clone(p.getId().toStdString());
        panel->setTop(playerContainer->getTop() + (playerContainer->getHeight())*position);
        playersStats->addChild(panel);

        //Fill the panel
        Ogre::OverlayElement* playerNameArea = ((Ogre::OverlayContainer*)panel)->getChild( p.getId().toStdString() + "/playerName");
        playerNameArea->setCaption(p.getName().toStdString() );
        Ogre::OverlayElement* playerDeathsArea = ((Ogre::OverlayContainer*)panel)->getChild( p.getId().toStdString() + "/playerDeaths");
        playerDeathsArea->setCaption(kills.toStdString());
        Ogre::OverlayElement* playerKillsArea = ((Ogre::OverlayContainer*)panel)->getChild( p.getId().toStdString() + "/playerKills");
        playerKillsArea->setCaption(QString::number(p.getDeaths()).toStdString());

        panel->show();

        if(p.getName() == mod->getName()){
            playerNameArea->setColour(Ogre::ColourValue::Red);
            playerDeathsArea->setColour(Ogre::ColourValue::Red);
            playerKillsArea->setColour(Ogre::ColourValue::Red);
        }

        position++;
    }

   statsOverlay->show();
}

void PlayerHUDManagement::hideStats(){
    statsOverlay->hide();
}

bool PlayerHUDManagement::statsAreVisible(){
    return statsOverlay->isVisible();
}
