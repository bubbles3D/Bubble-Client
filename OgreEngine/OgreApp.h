#ifndef APP_H
#define APP_H

#include <QThread>
#include <QList>
#include <QPair>
#include <QString>
#include <QVariant>
#include <OGRE/Ogre.h>
#include <OIS/OIS.h>
#include <stdlib.h>
#include <QMap>
#include "OGRE/Ogre.h"
#include "BaseApplication.h"
#include "model.h"
#include "OgreEngine/entityUtils.h"
#include "OgreEngine/cube.h"
#include "OgreEngine/playerHUDManagement.h"
//#include "OgreEngine/bubbleObject.h"
//#include "OgreEngine/playerObject.h"
//#include "OgreEngine/bulletobject.h"
//#include "OgreEngine/obstacleobject.h"
#include "OgreEngine/objectsManager.h"
#include "OgreEngine/face.h"
#include "OgreEngine/flagObject.h"


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#endif

Q_DECLARE_METATYPE( MODE )

class OgreApp : public QThread,  public BaseApplication
{
    Q_OBJECT

public:
    OgreApp(void);
    ~OgreApp(void);
    void run();

public slots:
    void changeMode(MODE mmode);

protected:
    OgreBites::SdkCameraMan* playerCameraController;
    enum MODE mode;
    Cube * cubeScene;
    ObjectsManager * objectMgr;

    virtual void createScene(void);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    virtual void createFrameListener(void);
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual void setupViewport(Ogre::SceneManager *curr,Ogre::String camera_Name);

};
#endif // APP_H

