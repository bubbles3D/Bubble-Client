#include "OgreApp.h"
#include "OGRE/Ogre.h"
#include <QDebug>
#include "face.h"


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

bool OgreApp::handleQuit(const CEGUI::EventArgs &e)
{
    mShutDown = true;
    return true;
}

//-------------------------------------------------------------------------------------
void OgreApp::createScene(void)
{
    //Init CEGUI
    mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();

    CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

    CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");

    CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");
    CEGUI::MouseCursor::getSingleton().hide();

    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");

    CEGUI::Window *quit = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/QuitButton");

    quit->setText("Quit");
    quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    sheet->addChildWindow(quit);
    CEGUI::System::getSingleton().setGUISheet(sheet);

    quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&OgreApp::handleQuit, this));

    // Set ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);

    Ogre::MeshManager::getSingleton();

    // Set camera look point
    mCamera->setPosition(40, 100, 580);
    mCamera->pitch(Ogre::Degree(0));
    mCamera->yaw(Ogre::Degree(0));
    setupViewport(mSceneMgr,mCamera->getName());

    //Initialise playerCamera
    playerCamera = mSceneMgr->createCamera("playerCamera");
    mRotateSpeed = 0.15f;

    //Scene
    Ogre::Entity* cube = mSceneMgr->createEntity("cube", "BoxTest.mesh");

    Ogre::SceneNode* cubeNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    cubeNode->setPosition(0,55,0);
    cubeNode->attachObject(cube);

    //Ball
    Ogre::Entity* bullet = mSceneMgr->createEntity("ball", "Bullet.mesh");
    Ogre::SceneNode* bulletNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    bulletNode->setPosition(200,55,0);
    bulletNode->scale(40,40,40);
    bulletNode->attachObject(bullet);

    //Create the cube
    Model * mod = Model::getInstance();
    cubeScene = new Cube(mod->getMapLength(),mSceneMgr, "Croix.png" , 0.2);

    //Init mode
    mode = FREE;

    Ogre::Entity* cube41 = mSceneMgr->createEntity("cube41", "Cube.mesh");
    Ogre::SceneNode* cubeNode41 =
    mSceneMgr->getRootSceneNode()->createChildSceneNode();
    cubeNode41->setPosition(400, 55, 0);
    cubeNode41->attachObject(cube41);
    entityUtils::initScale(cube41,cubeNode41);
    cubeNode41->scale(20,20,20);

    Ogre::Entity* cube74 = mSceneMgr->createEntity("ezr", "Bubble-Gum-Anim.mesh");
    qDebug()<<"BUBBLE";
    qDebug()<<entityUtils::getEdgeLength(cube74);

    //Set up the scene
    Model *model = Model::getInstance();
    objectUtils::updateObjectsStates("Cube.mesh", model->getUpdatedObstacles(), mSceneMgr);

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
        break;
    case MENU:
        //Need to inject timestamps to CEGUI System.
        CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);

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

    //TEST plane
    if(arg.key == OIS::KC_F7)   //
    {
        plane = BOTTOM;
        //playerNode->setOrientation(playerNode->getInitialOrientation());
        //playerNode->pitch(Ogre::Degree(-90));
    }
    else if (arg.key == OIS::KC_F8)   //
    {
       plane = XSIDE_OP;
       //playerNode->pitch(Ogre::Degree(+90));
    } else if (arg.key == OIS::KC_F9)   //
    {
       plane = XSIDE;
       //playerNode->pitch(Ogre::Degree(-90));
    } else if (arg.key == OIS::KC_F10)   //
    {
       plane = ZSIDE;
       //playerNode->roll(Ogre::Degree(-90));
    }else if (arg.key == OIS::KC_F11)   //
    {
       plane = ZSIDE_OP;
       //playerNode->roll(Ogre::Degree(+90));
    }else if (arg.key == OIS::KC_F12)   //
    {
       plane = TOP;
       //playerNode->roll(Ogre::Degree(+180));
    }

    //Local touch
    Model  * model = Model::getInstance();
    QString keyName;

    switch(mode){
    case FREE:
        //qDebug()<<"PASS IT";
        mCameraMan->injectKeyDown(arg);       
        switch (arg.key) {
         case OIS::KC_F1 :
                mode = FIRST;
                setupViewport(mSceneMgr,playerCamera->getName());

            break;
        case OIS::KC_F2 :
           mode = MENU;
           CEGUI::MouseCursor::getSingleton().show();
            break;
        default:
            break;
        }
        break;
    case FIRST:

         switch (arg.key) {
        case OIS::KC_UP:
            keyName = "UP";
            model->updateKeys(keyName, true);
            break;
        case OIS::KC_DOWN:
            keyName = "DOWN";
            model->updateKeys(keyName, true);
            break;
        case OIS::KC_RIGHT:
            keyName = "RIGHT";
            model->updateKeys(keyName, true);
            break;
        case OIS::KC_LEFT:
            keyName = "LEFT";
            model->updateKeys(keyName, true);
            break;
         case OIS::KC_F2 :
            mode = MENU;
            CEGUI::MouseCursor::getSingleton().show();
            break;
         case OIS::KC_F3 :
            mode = FREE;
            setupViewport(mSceneMgr,mCamera->getName());
        default:
            break;
        }
             break;
    case MENU:
        switch (arg.key) {
        case OIS::KC_F1 :
            mode = FIRST;
            CEGUI::MouseCursor::getSingleton().hide();
            setupViewport(mSceneMgr,playerCamera->getName());
            break;
         case OIS::KC_F3 :
            mode = FREE;
            CEGUI::MouseCursor::getSingleton().hide();
            setupViewport(mSceneMgr,mCamera->getName());
        default:
            break;
        }
        CEGUI::System &sys = CEGUI::System::getSingleton();
        sys.injectKeyDown(arg.key);
        sys.injectChar(arg.text);
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
            keyName = "UP";
            model->updateKeys(keyName, false);
            break;
        case OIS::KC_DOWN:
            keyName = "DOWN";
            model->updateKeys(keyName, false);
            break;
        case OIS::KC_RIGHT:
            keyName = "RIGHT";
            model->updateKeys(keyName, false);
            break;
        case OIS::KC_LEFT:
            keyName = "LEFT";
            model->updateKeys(keyName, false);
            break;
        default:
            break;
        }
             break;
        case MENU:
            CEGUI::System::getSingleton().injectKeyUp(arg.key);
        break;
    }

    return true;
}

bool OgreApp::mouseMoved( const OIS::MouseEvent &arg )
{
    Model * mod = Model::getInstance();
    CEGUI::System &sys = CEGUI::System::getSingleton();
    Ogre::Vector3 verticalVect;

    switch(mode){
    case FREE:
        mCameraMan->injectMouseMove(arg);

             break;
    case FIRST: 

        playerYawNode->yaw(Ogre::Degree(-arg.state.X.rel * mRotateSpeed));
        playerPitchNode->needUpdate();
        verticalVect = playerPitchNode->getOrientation() * Ogre::Vector3::UNIT_Z;
        verticalVect.normalise();
        if(arg.state.Y.rel < 0 && verticalVect.y > 0.9 || arg.state.Y.rel > 0 && verticalVect.y < -0.9){
            //Limit camera movement (looking up and down)
        }else{
            playerPitchNode->pitch(Ogre::Degree(+arg.state.Y.rel * mRotateSpeed));
        }
        //Transmit to server
        mod->updateMouse(playerTargetNode->_getDerivedPosition().x - playerNode->_getDerivedPosition().x,playerTargetNode->_getDerivedPosition().y - playerNode->_getDerivedPosition().y,playerTargetNode->_getDerivedPosition().z - playerNode->_getDerivedPosition().z);

        break;
    case MENU:
        sys.injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
        // Scroll wheel.
        if (arg.state.Z.rel){
           sys.injectMouseWheelChange(arg.state.Z.rel / 120.0f);
        }
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

        mod->shot(playerTargetNode->_getDerivedPosition().x - playerNode->_getDerivedPosition().x,playerTargetNode->_getDerivedPosition().y - playerNode->_getDerivedPosition().y,playerTargetNode->_getDerivedPosition().z - playerNode->_getDerivedPosition().z);
        break;
    case MENU:
        CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));
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
        CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));
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
     objectUtils::updateObjectsStates("Bullet.mesh", model->getUpdatedBullets(),mSceneMgr);

     //updateObjectsAnimations(model->getAllPlayers(), mSceneManager); // SEE LATER
     objectUtils::removeObjects(model->getClearedActors(),mSceneMgr);

 }

 void OgreApp::updatePlayersPositions(){
     Model * model = Model::getInstance();
     QList<Player> playerList = model->getUpdatedPlayers();

     //Update elements position
     foreach(Player p, playerList){

         Ogre::Node* node;
         Ogre::Node* pitchNode;
         Ogre::Node* yawNode;
         Ogre::Node* entityNode;

         try{
             //MAJ position des joueurs
             node = mSceneMgr->getRootSceneNode()->getChild(p.getId().toStdString());
             //MAJ orientation des joueurs
             yawNode = node->getChild(p.getId().toStdString()+"_rot");
             pitchNode = yawNode->getChild(p.getId().toStdString()+"_cam");
             entityNode = pitchNode->getChild(p.getId().toStdString()+"_entity");

         }catch (Ogre::Exception ex){
             //Si le joueur n'existe pas
             qDebug()<<"Creating players";
             Ogre::Entity* cube = mSceneMgr->createEntity(p.getId().toStdString(), "Bubble-Gum-Anim.mesh");
             node = mSceneMgr->getRootSceneNode()->createChildSceneNode(p.getId().toStdString());
             node->scale(20,20,20);
             yawNode = ((Ogre::SceneNode*)node)->createChildSceneNode(p.getId().toStdString() + "_rot", Ogre::Vector3(0,0,0));
             pitchNode = ((Ogre::SceneNode*)yawNode)->createChildSceneNode(p.getId().toStdString() + "_cam", Ogre::Vector3(0,0,0));
             entityNode = ((Ogre::SceneNode*)pitchNode)->createChildSceneNode(p.getId().toStdString() + "_entity", Ogre::Vector3(0,0,0));

             if(model->getName() == p.getName()){
                 //Si c'est notre joueur
                 playerEntityNode = ((Ogre::SceneNode*)entityNode);
                 playerPitchNode = ((Ogre::SceneNode*)pitchNode);
                 playerYawNode = ((Ogre::SceneNode*)yawNode);
                 playerTargetNode = playerPitchNode->createChildSceneNode(p.getId().toStdString() + "_target", Ogre::Vector3(0,0,1));
                 playerPitchNode->attachObject(playerCamera);
                 ((Ogre::SceneNode*)node)->setVisible(false,true);
                 playerCamera->rotate(Ogre::Vector3(0,1,0), Ogre::Angle(180));
                 setupViewport(mSceneMgr,playerCamera->getName());
                 playerNode = ((Ogre::SceneNode*)node);
                 playerSide =(side) p.getCube();
                 mode = FIRST;
             }
             ((Ogre::SceneNode*)entityNode)->attachObject(cube);
             qDebug()<<"Created players";
         }


         if(model->getName() != p.getName()){
            objectUtils::updateObjectState((Ogre::SceneNode*)node,(Ogre::SceneNode*)pitchNode,(Ogre::SceneNode*)yawNode,p);
         }else{
             // It's our player:

             //Set the player's main orientation according to the face of the cube

             switch(p.getCube()){
             //switch(plane){ //test
                 case(BOTTOM):
                     playerNode->setOrientation(playerNode->getInitialOrientation());
                     break;
                 case(ZSIDE_OP):
                     playerNode->setOrientation(playerNode->getInitialOrientation());
                     playerNode->roll(Ogre::Degree(+90));
                     break;
                 case(TOP):
                     playerNode->setOrientation(playerNode->getInitialOrientation());
                     playerNode->roll(Ogre::Degree(+180));
                 break;
                 case(ZSIDE):
                     playerNode->setOrientation(playerNode->getInitialOrientation());
                     playerNode->roll(Ogre::Degree(-90));
                     break;
                 case(XSIDE_OP):
                     playerNode->setOrientation(playerNode->getInitialOrientation());
                     playerNode->pitch(Ogre::Degree(-90));
                     break;
                 case(XSIDE):
                     playerNode->setOrientation(playerNode->getInitialOrientation());
                     playerNode->pitch(Ogre::Degree(+90));
                     break;
             }

             // Set our player's orientation on face switching
             if(playerSide != p.getCube()){ // if we change of cube's face
             //if(playerSide != plane){ // test
                 Ogre::Vector3 directionToLookAt = playerTargetNode->_getDerivedPosition() - playerNode->_getDerivedPosition();
                 objectUtils::orientPlayerToDirection(playerNode, playerYawNode,playerPitchNode,(side) p.getCube(), directionToLookAt);
             }

             //Set our player's position
             node->setPosition(p.getX(),p.getY(),p.getZ());
             playerSide = (side) p.getCube();
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

 CEGUI::MouseButton OgreApp::convertButton(OIS::MouseButtonID buttonID)
 {
     switch (buttonID)
     {
     case OIS::MB_Left:
         return CEGUI::LeftButton;

     case OIS::MB_Right:
         return CEGUI::RightButton;

     case OIS::MB_Middle:
         return CEGUI::MiddleButton;

     default:
         return CEGUI::LeftButton;
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
