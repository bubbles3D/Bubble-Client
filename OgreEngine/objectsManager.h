#ifndef OBJECTSMANAGER_H
#define OBJECTSMANAGER_H

#include "model.h"
#include "OgreEngine/playerHUDManagement.h"
#include "OgreEngine/bubbleObject.h"
#include "OgreEngine/mainPlayerObject.h"
#include "OgreEngine/bulletobject.h"
#include "OgreEngine/obstacleobject.h"
#include "OgreEngine/environnement.h"
#include "OgreEngine/flagObject.h"
#include <QString>

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

    void updateflagsState();

    //Destroy all objects in the list if they exist
    void destroyObjects(QList<QString> objectsToRemove);

    // return a pointer on the player
    MainPlayerObject * getPlayer();

    static void attachFlagToPlayer(QString idFlag, QString idPlayer);
    static void detachFlagFromPlayer(QString idPlayer);

    PlayerHUDManagement * getHUD();

protected:
    static Ogre::SceneManager * sceneMgr;
    static QMap<QString,Object*> objects;
    MainPlayerObject * player;

signals:
    void changeModeEvent(MODE mode);
};

#endif // OBJECTSMANAGER_H
