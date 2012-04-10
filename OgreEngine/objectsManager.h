#ifndef OBJECTSMANAGER_H
#define OBJECTSMANAGER_H

#include "model.h"
#include "OgreEngine/playerHUDManagement.h"
#include "OgreEngine/bubbleObject.h"
#include "OgreEngine/playerObject.h"
#include "OgreEngine/bulletobject.h"
#include "OgreEngine/obstacleobject.h"
#include "OgreEngine/environnement.h"

class ObjectsManager : public QObject
{
    Q_OBJECT

public:
    ObjectsManager(Ogre::SceneManager * msceneMgr);
    ~ObjectsManager();
    void updatePositions();
    void updatePlayersPositions();
    void updateBulletsState();
    void updateObstaclesStates();
    void destroyObjects(QList<QString> objectsToRemove);
    PlayerObject * getPlayer();

protected:
    Ogre::SceneManager * sceneMgr;
    QMap<QString,Object*> objects;
    PlayerObject * player;

signals:
    void changeModeEvent(MODE mode);
};

#endif // OBJECTSMANAGER_H
