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

