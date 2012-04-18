#include "objectsManager.h"

ObjectsManager::ObjectsManager(Ogre::SceneManager * msceneMgr):sceneMgr(msceneMgr)
{

}

void ObjectsManager::updatePositions(){
     Model * model = Model::getInstance();

     updatePlayersPositions();
     updateBulletsState();
     updateObstaclesStates();
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
           //obstacle->updateState(p);
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

MainPlayerObject * ObjectsManager::getPlayer(){
    return player;
}

PlayerHUDManagement * ObjectsManager::getHUD(){
    return player->getHUD();
}

ObjectsManager::~ObjectsManager(){
    Object* object;
    foreach(object,objects){
        delete(object);
    }
}

