#ifndef OBJECT_H
#define OBJECT_H

#include "OGRE/Ogre.h"
#include <QString>
#include <QDebug>

class Object
{
public:

    Object(Ogre::SceneManager * sceneMgr, float initialSize, QString name = "", Ogre::SceneNode * parentNode = 0);
    //Destroy all children nodes
    virtual ~Object();
    void setPosition(float x, float y, float z);
    void setPosition(Ogre::Vector3 pos);
    void setVisible(bool isVisible = true);
    virtual void setScale(float scale);
    virtual void setScale(Ogre::Vector3 scale);
    void attach(Ogre::SceneNode* nodeWhereAttach);
    Ogre::SceneNode * getNode();
    QString getName();
protected:

    // The root node
    Ogre::SceneNode* node;

    //the parent Node
    Ogre::SceneNode * parent;

    float meshInitialSize;

    //SceneManager
    Ogre::SceneManager * mSceneMgr;

    QString name;

    Ogre::Vector3 scale;
};

#endif // OBJECT_H
