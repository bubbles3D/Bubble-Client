#include "OgreApp.h"
#include "OGRE/Ogre.h"
#include <QDebug>
#include "face.h"
#include <stdlib.h>
#include <time.h>


//using namespace Ogre;

//-------------------------------------------------------------------------------------
OgreApp::OgreApp(void)
{

    qRegisterMetaType<MODE>("MODE");
}
//-------------------------------------------------------------------------------------
OgreApp::~OgreApp(void)
{
    exit();
}

//-------------------------------------------------------------------------------------
void OgreApp::createScene(void)
{
    objectMgr = new ObjectsManager(mSceneMgr);

    connect(objectMgr, SIGNAL(changeModeEvent(MODE)), this, SLOT(changeMode(MODE)));

    Ogre::ResourceManager::ResourceMapIterator iter = Ogre::FontManager::getSingleton().getResourceIterator();
    while (iter.hasMoreElements()) { iter.getNext()->load(); }

    // Set ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    // Set the free camera look point
    mCamera->setPosition(40, 100, 580);
    mCamera->pitch(Ogre::Degree(0));
    mCamera->yaw(Ogre::Degree(0));
    setupViewport(mSceneMgr,mCamera->getName());

    //Test------------------------------------------------------------------------
    Ogre::Entity* bullet = mSceneMgr->createEntity("ball", "Bullet.mesh");
    Ogre::SceneNode* bulletNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    bulletNode->setPosition(200,55,0);
    bulletNode->scale(40,40,40);
    bulletNode->attachObject(bullet);

    Ogre::SceneNode* cubeNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    Ogre::Entity* cubeEntity = mSceneMgr->createEntity("mycube", "Prefab_Cube");
    cubeNode->setPosition(500,50,0);cubeNode->setScale(100/100,100/100,100/100);
    cubeNode->attachObject(cubeEntity);

    //Just for see a little bubble along the x axis
    BubbleObject* bubble_test = new BubbleObject(mSceneMgr,"BUBBLE_TEST",BOTTOM,Ogre::Vector3(700,50,100),Ogre::Vector3(0,0,1),Ogre::Vector3(100,100,100),Ogre::ColourValue::White);

    //Flag test
    /*
    Ogre::Entity* flag = mSceneMgr->createEntity("flag", "mat.mesh");
    Ogre::SceneNode* flagNode = bubble_test->getNode()->createChildSceneNode();
    flagNode->setPosition(0,100,0);
    flagNode->setScale(5,50,5);
    flagNode->attachObject(flag);
    flagNode->setInheritScale(false);
    //ObstacleObject * flagNode= new ObstacleObject(mSceneMgr,Ogre::Vector3(10,100,10),"FlagRoot",Ogre::ColourValue(1,0,0,1),Ogre::Vector3(800,50,100));


    ObstacleObject * toile= new ObstacleObject(mSceneMgr,Ogre::Vector3(60,30,5),"Flag",Ogre::ColourValue(1,0,0,1),Ogre::Vector3(0,0,0),flagNode);
    toile->setPosition(7,0.6,0);
    toile->getNode()->setInheritScale(false);
    */
    FlagObject * flag2 = new FlagObject(mSceneMgr,"testss");//120
    flag2->setPosition(700,100,100);
    flag2->setScale(Ogre::Vector3(1,1,1));
    //End tests-------------------------------------------------------------------------

    //Create the cube
    Model * mod = Model::getInstance();

    Ogre::ColourValue rouge(255.0/255.0, 45.0/255.0, 45.0/255.0, 1);//Rouge
    Ogre::ColourValue jaune(249.0/255.0, 255.0/255.0, 58.0/255.0, 1);//Jaune
    Ogre::ColourValue vert(95.0/255.0, 255.0/255.0, 74.0/255.0, 1);//Vert
    Ogre::ColourValue bleu(71.0/255.0, 255.0/255.0, 231.0/255.0);//Bleu
    Ogre::ColourValue blanc(255/255.0, 255/255.0, 200/255.0);//Violet
    Ogre::ColourValue orange(249.0/255.0, 119.0/255.0, 20.0/255.0);//Orange

    cubeScene = new Cube(mod->getMapLength(),mSceneMgr, "Croix.png" , 0.33333, orange, blanc, jaune, rouge, vert, bleu);

    //Init mode
    mode = FREE;

    //Set up the scene
    objectMgr->updateObstaclesStates();

    //TEST for random color
    /* initialize random seed: */
      srand ( time(NULL) );

}

void OgreApp::createFrameListener(void){

    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    mInputManager = OIS::InputManager::createInputSystem( pl );

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);

    //Set initial mouse clipping size
    windowResized(mWindow);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

    mRoot->addFrameListener(this);
}

//-------------------------------------------------------------------------------------
bool OgreApp::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

    switch(mode){
    case FREE:
        mCameraMan->frameRenderingQueued(evt); //Update free cam
        objectMgr->updatePositions();
        break;
    case FIRST:
        objectMgr->updatePositions();
        objectMgr->getHUD()->updateHUD(evt.timeSinceLastFrame);
        break;
    case MENU:
        break;
    default:
        break;
    }

    return true;
}
//-------------------------------------------------------------------------------------
bool OgreApp::keyPressed( const OIS::KeyEvent &arg )
{

    if(arg.key == OIS::KC_F5)   // refresh all textures
    {
        Ogre::TextureManager::getSingleton().reloadAll();
    }
    else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
    {
        mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
    }
    else if (arg.key == OIS::KC_ESCAPE)
    {
        mShutDown = true;
    }

    //Local touch
    Model  * model = Model::getInstance();
    QString keyName;

    switch(mode){
    case FREE:
        mCameraMan->injectKeyDown(arg);       
        switch (arg.key) {
         case OIS::KC_F1 :
            changeMode(FIRST);

            break;
        case OIS::KC_F2 :
           mode = MENU;
           objectMgr->getPlayer()->setVisible(false);
            break;
        default:
            break;
        }
        break;
    case FIRST:

         switch (arg.key) {
        case OIS::KC_UP:
        case OIS::KC_Z:
            keyName = "UP";
            model->updateKeys(keyName, true);
            break;
        case OIS::KC_DOWN:
        case OIS::KC_S:
            keyName = "DOWN";
            model->updateKeys(keyName, true);
            break;
        case OIS::KC_RIGHT:
        case OIS::KC_D:
            keyName = "RIGHT";
            model->updateKeys(keyName, true);
            break;
        case OIS::KC_LEFT:
        case OIS::KC_Q:
            keyName = "LEFT";
            model->updateKeys(keyName, true);
            break;
         case OIS::KC_F2 :
            mode = MENU;
            objectMgr->getPlayer()->setVisible(false);

            break;
         case OIS::KC_F3 :
             changeMode(FREE);
            break;
         case OIS::KC_TAB :
             if(objectMgr->getHUD()->statsAreVisible() == false){
               objectMgr->getHUD()->displayStats();
             }else{
               objectMgr->getHUD()->hideStats();
             }

             break;
        default:
            break;
        }
             break;
    case MENU:
        switch (arg.key) {
        case OIS::KC_F1 :
            changeMode(FIRST);
            break;
         case OIS::KC_F3 :
            changeMode(FREE);
        default:
            break;
        }

        break;
    }
    return true;
}

bool OgreApp::keyReleased( const OIS::KeyEvent &arg )
{
    Model  * model = Model::getInstance();
    QString keyName;
    //
    switch(mode){
    case FREE:
        mCameraMan->injectKeyUp(arg);
             break;
    case FIRST:
        switch (arg.key) {
        case OIS::KC_UP:
        case OIS::KC_Z:
            keyName = "UP";
            model->updateKeys(keyName, false);
            break;
        case OIS::KC_DOWN:
        case OIS::KC_S:
            keyName = "DOWN";
            model->updateKeys(keyName, false);
            break;
        case OIS::KC_RIGHT:
        case OIS::KC_D:
            keyName = "RIGHT";
            model->updateKeys(keyName, false);
            break;
        case OIS::KC_LEFT:
        case OIS::KC_Q:
            keyName = "LEFT";
            model->updateKeys(keyName, false);
            break;
        case OIS::KC_TAB:

            break;
        default:
            break;
        }
             break;
        case MENU:

        break;
    }
    return true;
}

bool OgreApp::mouseMoved( const OIS::MouseEvent &arg )
{
    Model * mod = Model::getInstance();

    switch(mode){
    case FREE:
        mCameraMan->injectMouseMove(arg);

             break;
    case FIRST: 
        objectMgr->getPlayer()->mouseMouved(arg);
        //Transmit to server
        mod->updateMouse(objectMgr->getPlayer()->getPlayerDirection().x, objectMgr->getPlayer()->getPlayerDirection().y, objectMgr->getPlayer()->getPlayerDirection().z);

        break;
    case MENU:

        break;
    default:
        break;
    }

    return true;
}

bool OgreApp::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    Model *mod = Model::getInstance();
    switch(mode){
    case FREE:
        mCameraMan->injectMouseDown(arg, id);
        break;
    case FIRST:
        mod->shot(objectMgr->getPlayer()->getPlayerDirection().x, objectMgr->getPlayer()->getPlayerDirection().y, objectMgr->getPlayer()->getPlayerDirection().z);
        break;
    case MENU:

        break;
    default:
        break;
    }

    return true;
}

bool OgreApp::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{

    switch(mode){
    case FREE:
        mCameraMan->injectMouseUp(arg, id);
        break;
    case FIRST:
        break;
    case MENU:

        break;
    default:
        break;
    }

    return true;
}

 void OgreApp::run(){
     BaseApplication::go();
 }

 void OgreApp::setupViewport(Ogre::SceneManager *curr,Ogre::String camera_Name)
 {
     mWindow->removeAllViewports();

     Ogre::Camera *cam = curr->getCamera(camera_Name);
         cam->setNearClipDistance(5);
     Ogre::Viewport *vp = mWindow->addViewport(cam);

     vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
     cam->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
 }

 void OgreApp::changeMode(MODE mmode){
     switch(mmode){
      case(FIRST):
         mode = FIRST;
         objectMgr->getPlayer()->setVisible(false);
         setupViewport(mSceneMgr,objectMgr->getPlayer()->getPlayerCameraName());
         break;
      case(FREE):
         mode = FREE;
         setupViewport(mSceneMgr,mCamera->getName());
         objectMgr->getPlayer()->setVisible(true);
         break;
      case(MENU):
         break;
     }
 }

/*
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create OgreApp object
        OgreApp app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
*/
