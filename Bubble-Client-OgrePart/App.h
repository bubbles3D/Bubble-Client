#ifndef APP_H
#define APP_H

#include <OGRE/Ogre.h>
#include "OGRE/ExampleFrameListener.h"
#include <string.h>
#include <stdio.h>
#include "BaseApplication.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#endif

using namespace Ogre;

class Application : public BaseApplication
{
public:
    Application(void);
    virtual ~Application(void);


protected:
    virtual void createScene(void);/*
    virtual void chooseSceneManager(void);
    virtual void createFrameListener(void);
    virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool mousePressed(const OIS::MouseEvent &arg,OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent &arg,OIS::MouseButtonID id);
    bool mouseMovedCursor(const OIS::MouseEvent &arg);
    bool mouseMovedCibleur(const OIS::MouseEvent &arg);

    Ogre::SceneNode *mCurrentObject;	// The newly created object
    float mRotateSpeed;
    ExampleFrameListener* mFrameListener;
*/
};

#endif // APP_H

