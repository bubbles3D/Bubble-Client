#include "objectsManager.h"

Ogre::SceneManager* ObjectsManager::sceneMgr = 0;
QMap<QString,Object*> ObjectsManager::objects = QMap<QString,Object*>();

ObjectsManager::ObjectsManager(Ogre::SceneManager * msceneMgr)
{
    ObjectsManager::sceneMgr = msceneMgr;
}

void ObjectsManager::updatePositions(){
    Model * model = Model::getInstance();

    //Create flag if needed
    createFlags();

    updatePlayersPositions();
    updateBulletsState();
    updateObstaclesStates();
    updateflagsState();

    attachFlags();
    detachFlags();

    //updateObjectsAnimations(model->getAllPlayers(), mSceneManager); // SEE LATER
    destroyObjects(model->getClearedActors());
}

void ObjectsManager::processEvents(EventList events){

    QPair<BEvent, QList<QVariant> > event = events.pop();

    while(event.first != NONE_EVENT){
        switch(event.first){
        case CREATE:
            createObject(event.second);
            break;
        case UPDATE_ORIENTATION:
            break;
        case UPDATE_POSITION:
            break;
        case UPDATE_SCALE:
            break;
        case UPDATE_COLOR:
            break;
        case ATTACH:
            break;
        case START_DM:
            break;
        case START_CTF:
            break;
        case START_TDM:
            break;
        case ENDING_MATCH:
            break;
        case SET_PLAYER_SCORE:
            break;
        case SET_TEAM_SCORE:
            break;
        default:
            qDebug()<<"OBJMGR: ERROR PROCESSING EVENT";
            break;
        }

        event = events.pop();
    }
}
void ObjectsManager::createObject(QList<QVariant> params){
    OBJECT_TYPE type =(OBJECT_TYPE) (params.front().toInt());
    params.pop_front();
    createObject(type, params);
}

void ObjectsManager::createObject(OBJECT_TYPE type, QList<QVariant> params){
    QString id = params.front().toString();
    params.pop_front();

    float width = params.front().toFloat();
    params.pop_front();
    float height = params.front().toFloat();
    params.pop_front();
    float length = params.front().toFloat();
    params.pop_front();
    Ogre::Vector3 dim = Ogre::Vector3(width,height,length);

    float posX = params.front().toFloat();
    params.pop_front();
    float posY = params.front().toFloat();
    params.pop_front();
    float posZ = params.front().toFloat();
    params.pop_front();
    Ogre::Vector3 pos = Ogre::Vector3(posX,posY,posZ);

    float r = params.front().toFloat();
    params.pop_front();
    float g = params.front().toFloat();
    params.pop_front();
    float b = params.front().toFloat();
    params.pop_front();
    Ogre::ColourValue color = Ogre::ColourValue(r,g,b);

    Model * mod = Model::getInstance();

    //For players
    QString name;
    int mside;
    float Vx;
    float Vy;
    float Vz;
    Ogre::Vector3 V;
    int life;
    int kill;
    int death;


    if (!objects.contains(id)){
        Object * object;
        switch(type){
        case BUBBLE:
            name = params.front().toString();
            params.pop_front();
            mside = params.front().toInt();
            params.pop_front();
            Vx =params.front().toFloat();
            params.pop_front();
            Vy = params.front().toFloat();
            params.pop_front();
            Vz = params.front().toFloat();
            params.pop_front();
            V = Ogre::Vector3(Vx,Vy,Vz);

            life = params.front().toInt();
            params.pop_front();
            kill = params.front().toInt();
            params.pop_front();
            death = params.front().toInt();
            params.pop_front();

            object = new BubbleObject(sceneMgr,id, (side) mside, pos, V, dim, color);

            if(name == mod->getName()){
                qDebug()<<"NEW US"<<name;
                //If it's our player
                player = new MainPlayerObject(sceneMgr, id, (side) mside, pos, V, dim, color, life, kill, death);
                object = player;

                //Change mode view
                emit changeModeEvent(FIRST);
            }
            break;
        case BULLET:
            object = new BulletObject(sceneMgr,width,id, color, pos);
            break;
        case FLAG:
            object = new FlagObject(sceneMgr, id, color, pos);
            break;
        case OBSTACLE:
            object = new ObstacleObject(sceneMgr, dim, id, color, pos);
            break;
        }
        objects.insert(id, object);
    }else{
        qDebug()<<"OBJMNG: ERROR CREATING OBJECT (Id already used!!!)";
    }
}

void ObjectsManager::destroyObjects(QList<QString> objectsToRemove){
    foreach(QString s, objectsToRemove){
        delete(objects.value(s));
        objects.remove(s);
    }
}

void ObjectsManager::updateObstaclesStates(){
    Model * model = Model::getInstance();
    QList<Obstacles> obstacleList = model->getUpdatedObstacles();

    //Update elements position
    foreach(Obstacles p, obstacleList){
        ObstacleObject * obstacle;
        if (objects.contains(p.getId())){
            //Obstacle exist
            obstacle =(ObstacleObject*) objects.value(p.getId());
            obstacle->updateState(p);
        }else{
            //Color is ignored for now
            float r =1.0/(rand() % 5 + 1);
            float g =1.0/(rand() % 5 + 1);
            float b =1.0/(rand() % 5 + 1);
            //material->setDiffuse(r, g, b,0.5);
            //material->setAmbient(r, g, b);
            obstacle = new ObstacleObject(sceneMgr, p);
            obstacle->setColor(r,g,b);
            objects.insert(p.getId(), obstacle);
        }
    }
}
void ObjectsManager::updateBulletsState(){
    Model * model = Model::getInstance();
    QList<Bullet> bulletList = model->getUpdatedBullets();

    //Update elements position

    foreach(Bullet p, bulletList){
        BulletObject * bullet;

        if (objects.contains(p.getId())){
            bullet =(BulletObject*) objects.value(p.getId());
            bullet->updateState(p);
        }else{
            bullet = new BulletObject(sceneMgr, p);
            objects.insert(p.getId(), bullet);
        }
    }
}

void ObjectsManager::updatePlayersPositions(){
    Model * model = Model::getInstance();
    QList<Player> playerList = model->getUpdatedPlayers();

    //Update elements position
    foreach(Player p, playerList){
        BubbleObject * bubble;

        if (objects.contains(p.getId())){
            //Player exist
            bubble = (BubbleObject*)objects.value(p.getId());

            if(bubble == player){
                //If it's our player
                ((MainPlayerObject*)bubble)->updateState(p);
            }else{
                //If it's an other player
                bubble->updateState(p);
            }
        }else{
            if(p.getName() == model->getName()){
                qDebug()<<"NEW US"<<p.getName();
                //If it's our player
                player = new MainPlayerObject(sceneMgr, p);
                bubble = player;

                //FlagObject* flag = new FlagObject(sceneMgr,p.getId() + "FLAG");
                //flag->attach(bubble->getPitchNode());

                //Change mode view
                emit changeModeEvent(FIRST);
            }else{
                //If it's an other player
                qDebug()<<"NEW OTHER "<<p.getName();
                bubble = new BubbleObject(sceneMgr, (Actor) p);
            }
            objects.insert(p.getId(), bubble);

        }
    }
}

void ObjectsManager::updateflagsState(){
    /*
    Model * model = Model::getInstance();
    QList<Flag> flagList = model->getUpdatedFlags();

    //Update elements position

    foreach(Flag p, flagList){
        FlagObject * flag;
        if (objects.contains(p.getId())){
            flag =(FlagObject*) objects.value(p.getId());
            flag->updateState(p);
        }else{
            flag = new FlagObject(sceneMgr, p);
            objects.insert(p.getId(), flag);
        }
    }
*/
    Model * model = Model::getInstance();
    QList<Flag> flagList = model->getUpdatedFlags();

    //Update elements position

    foreach(Flag p, flagList){
        FlagObject * flag;
        if (objects.contains(p.getId())){
            flag =(FlagObject*) objects.value(p.getId());
            flag->updateState(p);
        }else{
            qDebug()<<"UPDATE FLAG DON T EXIST id:"<<p.getId();
        }
    }

}

void ObjectsManager::createFlag(Flag &p){
    FlagObject *flag = new FlagObject(sceneMgr, p);
    objects.insert(p.getId(), flag);
}

void ObjectsManager::createFlags(){

    Model * model = Model::getInstance();
    QList<Flag> flagList = model->getNewFlags();

    //Update elements position

    foreach(Flag p, flagList){
        if (objects.contains(p.getId())){
            qDebug()<<"ERROR CREATING FLAG: flag already exist!!! id:"<<p.getId();;
        }else{
            qDebug()<<"CREATE FLAG id:"<<p.getId();;
            createFlag(p);
        }
    }

}

void ObjectsManager::attachFlags(){
    Model * model = Model::getInstance();
    QList<QPair<QString, QString> > listToAttach =  model->getFlagsToAttach();
    QPair<QString, QString> p;

    foreach( p, listToAttach){
        if (objects.contains(p.first) && objects.contains(p.second)){
            attachFlagToPlayer(p.first, p.second);
        }else{
            qDebug()<<"ATTACH FLAG: player or flag DON T EXIST";
        }
    }

}

void ObjectsManager::detachFlags(){

    Model * model = Model::getInstance();
    QList<QString> listToDetach =  model->getFlagsToDettach();

    foreach(QString playerId, listToDetach){
        qDebug()<<"DETACHING";
        if (objects.contains(playerId)){
            detachFlagFromPlayer(playerId);
        }else{
            qDebug()<<"DETACH FLAG DON T EXIST";
        }
    }
}

MainPlayerObject * ObjectsManager::getPlayer(){
    return player;
}

PlayerHUDManagement * ObjectsManager::getHUD(){
    return player->getHUD();
}

void ObjectsManager::attachFlagToPlayer(QString idPlayer, QString idFlag){
    if(objects.contains(idFlag) && objects.contains(idPlayer)){
        FlagObject* flag = (FlagObject*)objects.value(idFlag);
        BubbleObject* player = (BubbleObject*)objects.value(idPlayer);
        flag->attach(player->getPitchNode());
        //flag->setPosition();
        player->setFlag(flag);

        qDebug()<<"ATTACH "<<endl;
        qDebug()<<"flag "<<flag->getName()<<flag->getNode()->getPosition().x<<" "<<flag->getNode()->getPosition().y<<" "<<flag->getNode()->getPosition().z;
        qDebug()<<"player "<<player->getName()<<player->getNode()->getPosition().x<<" "<<player->getNode()->getPosition().y<<" "<<player->getNode()->getPosition().z;
    }else{
        qDebug()<<"ERROR: attaching"<<objects.contains(idFlag)<<" "<<objects.contains(idPlayer);
    }
}

void ObjectsManager::detachFlagFromPlayer(QString idPlayer){

    BubbleObject* player = (BubbleObject*)objects[idPlayer];
    if(player->getFlag() != 0){
        qDebug()<<"DETACH FLAG";
        player->getFlag()->attach(sceneMgr->getRootSceneNode());
        //player->getFlag()->setOrientation(Ogre::Vector3(1,0,0),player->g);
        player->removeFlag();
    }else{
        qDebug()<<"ERROR: detaching flag (idPlayer: "<<idPlayer<<")";
    }

}

ObjectsManager::~ObjectsManager(){
    Object* object;
    foreach(object,objects){
        delete(object);
    }
}

