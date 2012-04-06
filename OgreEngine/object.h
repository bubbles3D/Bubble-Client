#ifndef OBJECT_H
#define OBJECT_H

#include "OGRE/Ogre.h"
#include <QString>
#include <QDebug>
class Object
{
public:

    Object(Ogre::SceneManager * sceneMgr, float initialSize, QString name = "");
    //Destroy all nodes' children
    ~Object();
    void setPosition(float x, float y, float z);
    virtual void setVisible(bool isVisible = true);
    virtual void setScale(float scale);
protected:

    // The root node
    Ogre::SceneNode* node;

    float meshInitialSize;

    //SceneManager
    Ogre::SceneManager * mSceneMgr;
};

#endif // OBJECT_H
