#ifndef APP_H
#define APP_H

#include <QThread>
#include <OGRE/Ogre.h>
#include "OGRE/ExampleFrameListener.h"
#include <string.h>
#include <stdio.h>
#include "BaseApplication.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#endif

using namespace Ogre;

class OgreApp : public BaseApplication, public QThread
{
public:
    OgreApp(void);
    ~OgreApp(void);
    void run();



protected:
    virtual void createScene(void);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

};
#endif // APP_H

