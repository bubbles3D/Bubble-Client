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

}
//-------------------------------------------------------------------------------------
OgreApp::~OgreApp(void)
{
    //BaseApplication::~BaseApplication();
    exit();
}

//-------------------------------------------------------------------------------------
void OgreApp::createScene(void)
{
    Ogre::ResourceManager::ResourceMapIterator iter = Ogre::FontManager::getSingleton().getResourceIterator();
    while (iter.hasMoreElements()) { iter.getNext()->load(); }

    // Set ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    // Set camera look point
    mCamera->setPosition(40, 100, 580);
    mCamera->pitch(Ogre::Degree(0));
    mCamera->yaw(Ogre::Degree(0));
    setupViewport(mSceneMgr,mCamera->getName());

    //Initialise playerCamera
    //playerCamera = mSceneMgr->createCamera("playerCamera");
    //mRotateSpeed = 0.15f;

    //Scene

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


    Ogre::SceneNode * spherNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("TEST");
    Ogre::Entity* sphere = mSceneMgr->createEntity("TEST", "Prefab_Sphere");
    Ogre::Entity* leftEye = mSceneMgr->createEntity("TEST2", "Prefab_Sphere");
    Ogre::Entity* rightEye = mSceneMgr->createEntity("TEST3", "Prefab_Sphere");


    Ogre::Node * yawNode = ((Ogre::SceneNode*)spherNode)->createChildSceneNode("_rot", Ogre::Vector3(0,0,0));
    Ogre::Node * pitchNode = ((Ogre::SceneNode*)yawNode)->createChildSceneNode("_cam", Ogre::Vector3(0,0,0));
    Ogre::Node * entityNode = ((Ogre::SceneNode*)pitchNode)->createChildSceneNode("_entity", Ogre::Vector3(0,0,0));
    Ogre::Node * leftEyesNode = ((Ogre::SceneNode*)pitchNode)->createChildSceneNode("_lEye", Ogre::Vector3(-15,15,39));
    Ogre::Node * rightEyesNode = ((Ogre::SceneNode*)pitchNode)->createChildSceneNode("_rEye", Ogre::Vector3(15,15,39));

    leftEyesNode->scale(0.3,0.4,0.2);
    leftEyesNode->pitch(Ogre::Degree(-20));
    rightEyesNode->scale(0.3,0.4,0.2);
    rightEyesNode->pitch(Ogre::Degree(-20));
    spherNode->scale(20.0/100.0,20.0/100.0,20.0/100.0);
    //Set the color

    Ogre::MaterialPtr mMaterial = Ogre::MaterialManager::getSingleton().create("_mat", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    sphere->setMaterialName("_mat");
    float r =1.0/(rand() % 5 + 1);
    float g =1.0/(rand() % 5 + 1);
    float b =1.0/(rand() % 5 + 1);
    mMaterial->setDiffuse(Ogre::ColourValue::White);
    mMaterial->setAmbient(Ogre::ColourValue::White);
    mMaterial->getTechnique(0)->getPass(0)->setLightingEnabled(false);


    Ogre::MaterialPtr mMaterial2 = Ogre::MaterialManager::getSingleton().create("_mat2", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    leftEye->setMaterialName("_mat2");
    rightEye->setMaterialName("_mat2");

    mMaterial2->setDiffuse(Ogre::ColourValue::Black);
    mMaterial2->setAmbient(Ogre::ColourValue::Black);

    spherNode->setPosition(700,20,100);
    ((Ogre::SceneNode*)entityNode)->attachObject(sphere);
    ((Ogre::SceneNode*)leftEyesNode)->attachObject(leftEye);
    ((Ogre::SceneNode*)rightEyesNode)->attachObject(rightEye);

    BubbleObject * bubbleTest = new BubbleObject(mSceneMgr,"bubbleTest", BOTTOM, Ogre::Vector3(1000,20,50),Ogre::Vector3(0,0,1),Ogre::Vector3(40,40,40), Ogre::ColourValue(0,0,1));
    delete(bubbleTest);
    //End tests--------------------------------------------------------------------------------------------------

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
    updateObstaclesStates();

    //Set up HUD
    //playerHUDMgt = new PlayerHUDManagement("FirstPerson/life", "FirstPerson/lens","FirstPerson/blood",40);

    //TEST for random color
    /* initialize random seed: */
      srand ( time(NULL) );

}

void OgreApp::createFrameListener(void){
    /*BaseApplication::createFrameListener();*/

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
        updatePositions();
        break;
    case FIRST:
        updatePositions();
        player->getHUD()->updateHUD(evt.timeSinceLastFrame);
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
                mode = FIRST;
                player->setVisible(false);
                setupViewport(mSceneMgr,player->getPlayerCameraName());

            break;
        case OIS::KC_F2 :
           mode = MENU;
           player->setVisible(false);
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
            player->setVisible(false);

            break;
         case OIS::KC_F3 :
            mode = FREE;
            setupViewport(mSceneMgr,mCamera->getName());
            player->setVisible(true);
            break;
         case OIS::KC_TAB :
             if(player->getHUD()->statsAreVisible() == false){
               player->getHUD()->displayStats();
             }else{
               player->getHUD()->hideStats();
             }

             break;
        default:
            break;
        }
             break;
    case MENU:
        switch (arg.key) {
        case OIS::KC_F1 :
            mode = FIRST;
            setupViewport(mSceneMgr,player->getPlayerCameraName());
            player->setVisible(false);
            break;
         case OIS::KC_F3 :
            mode = FREE;
            player->setVisible(true);
            setupViewport(mSceneMgr,player->getPlayerCameraName());
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

    Ogre::Vector3 verticalVect;

    switch(mode){
    case FREE:
        mCameraMan->injectMouseMove(arg);

             break;
    case FIRST: 

        player->mouseMouved(arg);


        //Transmit to server
        mod->updateMouse(player->getPlayerDirection().x, player->getPlayerDirection().y, player->getPlayerDirection().z);

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
        mod->shot(player->getPlayerDirection().x, player->getPlayerDirection().y, player->getPlayerDirection().z);
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

 void OgreApp::updatePositions(){
      Model * model = Model::getInstance();
     updatePlayersPositions();

     updateBulletsState();

     //updateObjectsAnimations(model->getAllPlayers(), mSceneManager); // SEE LATER
     objectUtils::removeObjects(model->getClearedActors(),mSceneMgr);

 }
void OgreApp::updateObstaclesStates(){
    Model * model = Model::getInstance();
    QList<Obstacles> obstacleList = model->getUpdatedObstacles();

    //Update elements position
    foreach(Obstacles p, obstacleList){
        ObstacleObject * obstacle;

        //if (obstacles.contains(p.getId())){
            //Obstacle exist
        //    obstacle = obstacles.value(p.getId());
            //obstacle->updateState(p); SEE later
        //}else{
            //If it's an other player
            obstacle = new ObstacleObject(mSceneMgr, p);
            //bullets.insert(p.getId(), bullet); SEE later
        //}
    }
}
 void OgreApp::updateBulletsState(){
     Model * model = Model::getInstance();
     QList<Bullet> bulletList = model->getUpdatedBullets();

     //Update elements position
     foreach(Bullet p, bulletList){
         BulletObject * bullet;

         if (bullets.contains(p.getId())){
             bullet = bullets.value(p.getId());
             bullet->updateState(p);
         }else{
             bullet = new BulletObject(mSceneMgr, p);
             bullets.insert(p.getId(), bullet);
         }
     }
 }


 void OgreApp::updatePlayersPositions(){
     Model * model = Model::getInstance();
     QList<Player> playerList = model->getUpdatedPlayers();

     //Update elements position
     foreach(Player p, playerList){
         BubbleObject * bubble;

         if (players.contains(p.getId())){
             //Player exist
             bubble = players.value(p.getId());

             if(bubble == player){
                 //If it's our player
                 ((PlayerObject*)bubble)->updateState(p);
             }else{
                 //If it's an other player
                bubble->updateState(p);
             }
         }else{
             if(p.getName() == model->getName()){
                 qDebug()<<"NEW US"<<p.getName();
                 //If it's our player
                 player = new PlayerObject(mSceneMgr, p);
                 bubble = player;
             }else{
                 //If it's an other player
                 qDebug()<<"NEW OTHER "<<p.getName();
                bubble = new BubbleObject(mSceneMgr, (Actor) p);
             }
             players.insert(p.getId(), bubble);
         }
     }
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
