#ifndef OBJECTUTILS_H
#define OBJECTUTILS_H

#include "OGRE/Ogre.h"
#include "actor.h"
#include "bullet.h"
#include "obstacles.h"
#include "entityUtils.h"
#include "player.h"
#include "environnement.h"

//using namespace Ogre;

class objectUtils{
public:
    static void orientPlayerToDirection(Ogre::SceneNode * playerNode, Ogre::SceneNode * yawNode, Ogre::SceneNode * pitchNode, side floor, Ogre::Vector3 directionToLookAt);
    static void updateObjectState(Ogre::SceneNode* node, Ogre::SceneNode* pitchNode, Ogre::SceneNode* yawNode, Actor p);
    static void removeObject(QString name, Ogre::SceneManager* mSceneMgr);
    static void updateObjectAnimation(Actor p, const char * animation, Ogre::SceneManager * sceneMgr);
    static void updateObjectsAnimations(QList<Player> objectsList, Ogre::SceneManager * sceneMgr);
    static void removeObjects(QList<QString> names, Ogre::SceneManager * sceneMgr);
    static void updateObjectsStates(const char * meshName, QList<Obstacles> objectsList, Ogre::SceneManager * sceneManager);
    static void updateObjectsStates(const char * meshName, QList<Bullet> objectsList, Ogre::SceneManager * sceneManager);
};

#endif // OBJECTUTILS_H
