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

    //Update (or create) all positions, scales, colors and orientations of all updated objects
    void updatePositions();

    //Update (or create) only updated players state
    void updatePlayersPositions();

    //Update (or create) only updated bullets state
    void updateBulletsState();

    //Update (or create) only updated obstacles state
    void updateObstaclesStates();

    //Destroy all objects in the list if they exist
    void destroyObjects(QList<QString> objectsToRemove);

    // return a pointer on the player
    PlayerObject * getPlayer();

protected:
    Ogre::SceneManager * sceneMgr;
    QMap<QString,Object*> objects;
    PlayerObject * player;

signals:
    void changeModeEvent(MODE mode);
};

#endif // OBJECTSMANAGER_H
