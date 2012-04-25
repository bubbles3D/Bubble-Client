#include "OgreEngine/playerHUDManagement.h"
#include <QDebug>
#include <OGRE/OgreTextAreaOverlayElement.h>

float PlayerHUDManagement::alphaBlood = 0;
bool PlayerHUDManagement::statVisible = false;
bool PlayerHUDManagement::startingGame = false;
bool PlayerHUDManagement::runningGame= false;
bool PlayerHUDManagement::endingGame= false;
bool playersLessThan(Player &s1, Player &s2);

PlayerHUDManagement::PlayerHUDManagement(QString overlayLifeName, QString overlayLensName, QString overlayBloodName, float maxLifeValue, float maxLifeSize):
    maxLife(maxLifeValue), maxLifeSize(maxLifeSize)
{
    statsOverlay = 0;
    playerContainer = 0;
    statsPanel = 0;
    playersStats = 0;
    runningGame = false;

    lifeOverlay = Ogre::OverlayManager::getSingleton().getByName(overlayLifeName.toStdString());
    if(lifeOverlay){
         //lifeOverlay->show();
         lifeContainer = lifeOverlay->getChild("life");

    }else{
        //If we have not succed to retreive the life overlay
        lifeContainer = 0;

    }

    lensOverlay = Ogre::OverlayManager::getSingleton().getByName(overlayLensName.toStdString());
    if(lensOverlay){
         //lensOverlay->show();
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
        //scoreOverlay->show();
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
        playersStats = (Ogre::OverlayContainer*) statsPanel->getChild("playersStats");
        playerContainer = playersStats->getChild("playerStat");
        playerContainer->hide();
        ((Ogre::OverlayContainer*)playersStats)->removeChild(playerContainer->getName());

    }else{
        //If we have not succed to retreive the life overlay
        playersStats = 0;
        playerContainer = 0;
        qDebug()<<"ERROR Stats Overlay missing";
    }

    timeOverlay = Ogre::OverlayManager::getSingleton().getByName("FirstPerson/time");
    if(timeOverlay){
        timeContainer = timeOverlay->getChild("RemainingTime");
    }else{
        //If we have not succed to retreive the life overlay
        timeContainer = 0;
        qDebug()<<"ERROR time Overlay missing";
    }

    flagOverlay = Ogre::OverlayManager::getSingleton().getByName("FirstPerson/flag");
    if(flagOverlay){
        flagsPanel =  flagOverlay->getChild("flags");
        flagPanel =  (Ogre::OverlayContainer*)flagsPanel->getChild("flag");
        flagsPanel->removeChild(flagPanel->getName());

    }else{
        //If we have not succed to retreive the flag overlay
        flagsPanel = 0;
        flagPanel = 0;
        qDebug()<<"ERROR flag Overlay missing";
    }

    gameMode = INIT;
    setTime("0:00");
    setGameMode(NO_MODE);


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

    //Update stats panel
    if(statVisible == true && statsAreVisible() == false){
        displayDMStats();
    }else{
        if(statVisible == false && statsAreVisible() == true){
            statsOverlay->hide();
        }
    }

    //update time
    Model* mod = Model::getInstance();
    int min =(int) mod->getRemainingTime()/60;
    int sec = (int) mod->getRemainingTime() % 60;
    QString time = QString::number(min) + ":" + QString::number(sec);
    setTime(time);
/*
    QPair<QString,QMap<QString,int> > score = mod->getScores();

    if(endingGame == true){//A match just end
        qDebug()<<"ENDING GAME";
        flagOverlay->hide();
        endingGame = false;
        runningGame = false;
        if(score.first == "CTF" || score.first == "TDM"){
            cleanFlags();
        }
    }

    if(runningGame == true){//A match is running
        qDebug()<<"RUNNING GAME";
        if(score.first == "CTF" || score.first == "TDM"){
            foreach( QString key, score.second.keys() ){
                setFlagScore(key,score.second.value(key));
            }
        }
    }

    if(startingGame == true){//A match just start
       qDebug()<<"STARTING GAME";
       startingGame = false;
       runningGame = true;

       if(score.first == "CTF" || score.first == "TDM"){
           qDebug()<<"STARTING GAME: CTF";
           foreach( QString key, score.second.keys() )
           {
               addFlag(key,Ogre::ColourValue::Blue,2,0);
           }
           flagOverlay->show();
       }else{

       }
    }
*/
    /*addFlag("rreeff",Ogre::ColourValue::Blue,2,0);
    addFlag("rreeff2",Ogre::ColourValue::Red,1,1);
    addFlag("rreeff3",Ogre::ColourValue::Green,3,2);
    setFlagScore("rreeff2",2);

    flagOverlay->show();*/
}

void PlayerHUDManagement::updateBlood(float timeSinceLastFrame){
    if(PlayerHUDManagement::alphaBlood > 0){
        setAlphaBlood(PlayerHUDManagement::alphaBlood);
        PlayerHUDManagement::alphaBlood = PlayerHUDManagement::alphaBlood - PlayerHUDManagement::alphaBlood * timeSinceLastFrame;
    }else{
       PlayerHUDManagement::alphaBlood = 0;
    }
}

void PlayerHUDManagement::setLife(float lifeValue, Ogre::ColourValue color){
    float lifeSize = convertLifeToSize(lifeValue);
    OverlayUtils::setScaleKeepingCenter(lifeContainer,lifeSize,lifeSize);

    if(lifeValue == 1){
        setLifeColor(Ogre::ColourValue::Red);
    }else{
        setLifeColor(color);
    }
}

void PlayerHUDManagement::setLifeColor(Ogre::ColourValue lifeColor){
    Ogre::TextureUnitState * lifeTex = lifeContainer->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0);
    lifeTex->setColourOperationEx(Ogre::LBX_MODULATE,Ogre::LBS_TEXTURE,Ogre::LBS_MANUAL,Ogre::ColourValue::White,lifeColor);
}

float PlayerHUDManagement::convertLifeToSize(float lifeValue){
    return maxLifeSize*(1 - (maxLife - lifeValue)/maxLife ) ;
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
void PlayerHUDManagement::cleanStats(Ogre::OverlayContainer* node){

    OverlayUtils::destroyAllOverlayContainerChildren(node);

    Ogre::OverlayContainer::ChildIterator ci = ((Ogre::OverlayContainer*)node)->getChildIterator();
    while (ci.hasMoreElements())
    {
        Ogre::OverlayElement* child = ci.getNext();
        Ogre::MaterialManager::getSingleton().remove((Ogre::ResourcePtr&)(child->getMaterial()));
    }
}

void PlayerHUDManagement::displayDMStats(){
    cleanStats(playersStats);

    Model * mod = Model::getInstance();
    QList<Player> players(mod->getAllPlayers());

    qSort(players.begin(),players.end(),playersLessThan);

    int position = 0;
    foreach(Player p, players){
        QString kills = QString::number(p.getKills()) ;
        QString deaths = QString::number(p.getDeaths()) ;

        // Create a player panel
        Ogre::OverlayElement* panel= playerContainer->clone(p.getId().toStdString());
        panel->setTop(playerContainer->getTop() + (playerContainer->getHeight())*position);
        playersStats->addChild(panel);

        //Fill the panel
        Ogre::OverlayElement* playerNameArea = ((Ogre::OverlayContainer*)panel)->getChild( p.getId().toStdString() + "/playerName");
        playerNameArea->setCaption(p.getName().toStdString() );
        Ogre::OverlayElement* playerDeathsArea = ((Ogre::OverlayContainer*)panel)->getChild( p.getId().toStdString() + "/playerDeaths");
        playerDeathsArea->setCaption(deaths.toStdString());
        Ogre::OverlayElement* playerKillsArea = ((Ogre::OverlayContainer*)panel)->getChild( p.getId().toStdString() + "/playerKills");
        playerKillsArea->setCaption(kills.toStdString());
        Ogre::ColourValue color;
        p.getColor(&(color.r),&(color.g),&(color.b));


        Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().getByName("PlayerPanel");
        mat->clone(p.getId().toStdString() + "_stat_mat");

        panel->setMaterialName(p.getId().toStdString() + "_stat_mat");

        Ogre::TextureUnitState * panelTex = panel->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0);
        panelTex->setColourOperationEx(Ogre::LBX_MODULATE,Ogre::LBS_TEXTURE,Ogre::LBS_MANUAL,Ogre::ColourValue::White,color);
        panel->show();

        //Set player text to red or blue
        if(p.getName() == mod->getName()){
            if(color.r > 0.8 && color.g < 0.1 && color.b < 0.1){
                playerNameArea->setColour(Ogre::ColourValue::White);
                playerDeathsArea->setColour(Ogre::ColourValue::White);
                playerKillsArea->setColour(Ogre::ColourValue::White);
            }else{
                playerNameArea->setColour(Ogre::ColourValue::Red);
                playerDeathsArea->setColour(Ogre::ColourValue::Red);
                playerKillsArea->setColour(Ogre::ColourValue::Red);
            }

        }

        position++;
    }

   statsOverlay->show();
/*
    //Clean old stats (to move in a new methode)
    cleanStats(playersStats);

    Model * mod = Model::getInstance();
    QList<Player> players(mod->getAllPlayers());

    qSort(players.begin(),players.end(),playersLessThan);

    int position = 0;
    foreach(Player p, players){
        QString kills = QString::number(p.getKills()) ;
        QString deaths = QString::number(p.getDeaths()) ;

        // Create a player panel
        Ogre::OverlayElement* panel= playerContainer->clone(p.getId().toStdString());
        panel->setTop(playerContainer->getTop() + (playerContainer->getHeight())*position);
        playersStats->addChild(panel);

        //Fill the panel
        Ogre::OverlayElement* playerNameArea = ((Ogre::OverlayContainer*)panel)->getChild( p.getId().toStdString() + "/playerName");
        playerNameArea->setCaption(p.getName().toStdString() );
        Ogre::OverlayElement* playerDeathsArea = ((Ogre::OverlayContainer*)panel)->getChild( p.getId().toStdString() + "/playerDeaths");
        playerDeathsArea->setCaption(deaths.toStdString());
        Ogre::OverlayElement* playerKillsArea = ((Ogre::OverlayContainer*)panel)->getChild( p.getId().toStdString() + "/playerKills");
        playerKillsArea->setCaption(kills.toStdString());

        panel->show();

        if(p.getName() == mod->getName()){
            playerNameArea->setColour(Ogre::ColourValue::Red);
            playerDeathsArea->setColour(Ogre::ColourValue::Red);
            playerKillsArea->setColour(Ogre::ColourValue::Red);
        }

        position++;
    }

   statsOverlay->show();
   */
}

void PlayerHUDManagement::displayCTFStats(){
    displayDMStats();
    //SEE LATER
}

void PlayerHUDManagement::displayStats(){

    statVisible = true;
    /*
    switch(gameMode){
    case DM:
        displayDMStats();

        break;
    case TDM:
        break;
    case CTF:
        displayDMStats();
        break;
    case NO_MODE:
        break;
    }
    */
}

void PlayerHUDManagement::hideStats(){
    statVisible = false;
}

bool PlayerHUDManagement::statsAreVisible(){
    return statsOverlay->isVisible();
}

void PlayerHUDManagement::setGameMode(GAME_MODE mode){
    if(gameMode != mode){
        gameMode = mode;
        switch(gameMode){
        case DM:
            break;
        case TDM:
        case CTF:
            //flagOverlay->show();
            //addFlag("rreeff",Ogre::ColourValue::Blue,2,0);
            //addFlag("rreeff2",Ogre::ColourValue::Red,1,1);
            //addFlag("rreeff3",Ogre::ColourValue::Green,3,2);
            //setFlagScore("rreeff2",2);

            flagOverlay->show();
            break;
        case NO_MODE:
            break;
        case INIT:
            break;
        }

        //In all cases
        lifeOverlay->show();
        lensOverlay->show();
        scoreOverlay->show();
        timeOverlay->show();


    }
}
void PlayerHUDManagement::startGame(){
    startingGame = true;
}

void PlayerHUDManagement::endGame(){
    endingGame = true;
}

void PlayerHUDManagement::setTime(QString time){
    timeContainer->setCaption(time.toStdString());
}

void PlayerHUDManagement::setFlagColor(Ogre::OverlayContainer * flagPan, Ogre::ColourValue flagColor){
    Ogre::OverlayElement * flagIcone = flagPan->getChild(flagPan->getName() + "/icone");

    Ogre::TextureUnitState * flagTex = flagIcone->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0);

    flagTex->setColourOperationEx(Ogre::LBX_MODULATE,Ogre::LBS_TEXTURE,Ogre::LBS_MANUAL,Ogre::ColourValue::White,flagColor);
}

void PlayerHUDManagement::setFlagScore(Ogre::OverlayContainer * flagPan, int flagnb){
    Ogre::OverlayElement* nbFlagArea = ((Ogre::OverlayContainer*)flagPan)->getChild( flagPan->getName() + "/nbFlag");
    nbFlagArea->setCaption(QString::number(flagnb).toStdString());
}

void PlayerHUDManagement::setFlagScore(QString id, int flagnb){
    Ogre::OverlayContainer* flagPan = (Ogre::OverlayContainer*)((Ogre::OverlayContainer*)flagsPanel)->getChild(id.toStdString() + "/flag");
    setFlagScore(flagPan, flagnb);
}

void PlayerHUDManagement::cleanFlags(){

    Ogre::OverlayContainer::ChildIterator ci = ((Ogre::OverlayContainer*)flagsPanel)->getChildIterator();

    while (ci.hasMoreElements())
    {
        Ogre::OverlayElement* child = ci.getNext();
        //QString a = QString(((std::basic_string<char>)  child->getName()).c_str());

        //qDebug()<<"3:"<<a;
        Ogre::OverlayElement * flagIcone = ((Ogre::OverlayContainer*)child)->getChild(child->getName() + "/icone");
        Ogre::MaterialManager::getSingleton().remove(flagIcone->getMaterial().getPointer()->getName());
    }
    OverlayUtils::destroyAllOverlayContainerChildren((Ogre::OverlayContainer*)flagsPanel);
}

void PlayerHUDManagement::addFlag(QString id,Ogre::ColourValue flagColor, int score, int position){
    // Create a player panel
    Ogre::OverlayContainer* panel= (Ogre::OverlayContainer*) flagPanel->clone(id.toStdString());
    panel->setLeft(flagPanel->getLeft() + (flagPanel->getWidth())*position);
    flagsPanel->addChild(panel);

    //update the panel
    Ogre::OverlayElement* nbFlagArea = ((Ogre::OverlayContainer*)panel)->getChild( panel->getName() + "/nbFlag");
    nbFlagArea->setCaption(QString::number(score).toStdString());

    //Create the material
    Ogre::OverlayElement * flagIcone = panel->getChild(panel->getName() + "/icone");

    flagIcone->getMaterial().getPointer()->clone(id.toStdString()+"_flag_mat");
    flagIcone->setMaterialName(id.toStdString()+"_flag_mat");
    setFlagColor(panel,flagColor);

    panel->show();

}

bool playersLessThan(Player &s1, Player &s2)
{
    bool returnValue;
    if(s1.getKills() == s2.getKills()){
        returnValue = s1.getDeaths() < s2.getDeaths();
    }else{
        returnValue = s1.getKills() > s2.getKills();
    }

    return returnValue;
}



