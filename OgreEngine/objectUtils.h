#ifndef OBJECTUTILS_H
#define OBJECTUTILS_H

#include "OGRE/Ogre.h"
#include "actor.h"
#include "bullet.h"
#include "obstacles.h"
#include "entityUtils.h"
#include "player.h"

using namespace Ogre;

enum side {
    BOTTOM=1, TOP=5, XSIDE=2, XSIDE_OP=4, ZSIDE=6, ZSIDE_OP=3
};

class objectUtils{
public:
    static void orientPlayerToDirection(SceneNode * playerNode, SceneNode * yawNode, SceneNode * pitchNode, side floor, Vector3 directionToLookAt);
    static void updateObjectState(SceneNode* node, SceneNode* pitchNode, SceneNode* yawNode, Actor p);
    static void removeObject(QString name, SceneManager* mSceneMgr);
    static void updateObjectAnimation(Actor p, const char * animation, SceneManager * sceneMgr);
    static void updateObjectsAnimations(QList<Player> objectsList, SceneManager * sceneMgr);
    static void removeObjects(QList<QString> names, SceneManager * sceneMgr);
    static void updateObjectsStates(const char * meshName, QList<Obstacles> objectsList, SceneManager * sceneManager);
    static void updateObjectsStates(const char * meshName, QList<Bullet> objectsList, SceneManager * sceneManager);
};

#endif // OBJECTUTILS_H
