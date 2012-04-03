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
    playerCamera = mSceneMgr->createCamera("playerCamera");
    mRotateSpeed = 0.15f;

    //Scene

    //Ball Test
    Ogre::Entity* bullet = mSceneMgr->createEntity("ball", "Bullet.mesh");
    Ogre::SceneNode* bulletNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    bulletNode->setPosition(200,55,0);
    bulletNode->scale(40,40,40);
    bulletNode->attachObject(bullet);

    Ogre::Entity* cube74 = mSceneMgr->createEntity("ezr", "Bubble-Gum-Anim.mesh");
    qDebug()<<entityUtils::getEdgeLength(cube74);

    //End tests

    //Create the cube
    Model * mod = Model::getInstance();

    Ogre::ColourValue rouge(255.0/255.0, 45.0/255.0, 45.0/255.0, 1);//Rouge
    Ogre::ColourValue jaune(255.0/255.0, 255.0/255.0, 74.0/255.0, 1);//Jaune
    Ogre::ColourValue vert(95.0/255.0, 255.0/255.0, 74.0/255.0, 1);//Vert
    Ogre::ColourValue bleu(71.0/255.0, 255.0/255.0, 231.0/255.0);//Bleu
    Ogre::ColourValue blanc(255/255.0, 255/255.0, 200/255.0);//Violet
    Ogre::ColourValue orange(255.0/255.0, 195.0/255.0, 31.0/255.0);//Orange

    cubeScene = new Cube(mod->getMapLength(),mSceneMgr, "Croix.png" , 0.33333, orange, blanc, jaune, rouge, vert, bleu);

    //Init mode
    mode = FREE;

    //Set up the scene
    Model *model = Model::getInstance();
    objectUtils::updateObjectsStates("Cube.mesh", model->getUpdatedObstacles(), mSceneMgr);

    //Set up HUD
    playerHUDMgt = new PlayerHUDManagement("FirstPerson/life", "FirstPerson/lens","FirstPerson/blood",40);

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
        playerHUDMgt->updateHUD(evt.timeSinceLastFrame);
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
        mCameraMan->injectKeyDown(arg);       
        switch (arg.key) {
         case OIS::KC_F1 :
                mode = FIRST;
                setupViewport(mSceneMgr,playerCamera->getName());

            break;
        case OIS::KC_F2 :
           mode = MENU;

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

            break;
         case OIS::KC_F3 :
            mode = FREE;
            setupViewport(mSceneMgr,mCamera->getName());
            break;
         case OIS::KC_TAB :
             if(playerHUDMgt->statsAreVisible() == false){
                 playerHUDMgt->displayStats();
             }else{
                playerHUDMgt->hideStats();
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
            setupViewport(mSceneMgr,playerCamera->getName());
            break;
         case OIS::KC_F3 :
            mode = FREE;
            setupViewport(mSceneMgr,mCamera->getName());
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

        playerYawNode->yaw(Ogre::Degree(-arg.state.X.rel * mRotateSpeed));
        playerPitchNode->needUpdate();
        verticalVect = playerPitchNode->getOrientation() * Ogre::Vector3::UNIT_Z;
        verticalVect.normalise();
        if( (arg.state.Y.rel < 0 && verticalVect.y > 0.9) || (arg.state.Y.rel > 0 && verticalVect.y < -0.9)){
            //Limit camera movement (looking up and down)
        }else{
            playerPitchNode->pitch(Ogre::Degree(+arg.state.Y.rel * mRotateSpeed));
        }
        //Transmit to server
        mod->updateMouse(playerTargetNode->_getDerivedPosition().x - playerNode->_getDerivedPosition().x,playerTargetNode->_getDerivedPosition().y - playerNode->_getDerivedPosition().y,playerTargetNode->_getDerivedPosition().z - playerNode->_getDerivedPosition().z);

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
        mod->shot(playerTargetNode->_getDerivedPosition().x - playerNode->_getDerivedPosition().x,playerTargetNode->_getDerivedPosition().y - playerNode->_getDerivedPosition().y,playerTargetNode->_getDerivedPosition().z - playerNode->_getDerivedPosition().z);
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

             /*Ogre::MaterialPtr mMaterial = Ogre::MaterialManager::getSingleton().create(p.getId().toStdString()+"_mat", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);


                 Ogre::Pass * pass = mMaterial->getTechnique(0)->getPass(0);
                 pass->setLightingEnabled(false);
                 pass->setDepthWriteEnabled(false);
                 pass->setPolygonMode(Ogre::PM_SOLID);
                 pass->setAmbient(Ogre::ColourValue(0,1,0,1));
                 pass->setDiffuse(Ogre::ColourValue(0,1,0,1));
                 //pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
                 //pass->setAlphaRejectValue(128);
                 pass->setDepthCheckEnabled(true);
                 pass->setNormaliseNormals(true);
                 //pass->setTransparentSortingEnabled(true);
                 Ogre::TextureUnitState * texture = pass->createTextureUnitState(p.getId().toStdString()+"_tex");
                 texture->setTextureName("White-Eyes.png");
                 texture->setTextureAddressingMode(Ogre::TextureUnitState::TAM_CLAMP);
                 texture->setTextureScale(1,1);
                 //texture->setAlphaOperation();
                 //texture->setColourOperation(Ogre::LBO_MODULATE);//
                 //texture->setColourOperationEx(Ogre::LBX_MODULATE,Ogre::LBS_TEXTURE,Ogre::LBS_MANUAL,Ogre::ColourValue::White,Ogre::ColourValue(0,0,1,1));

                 //Ogre::TextureUnitState * texture2 = pass->createTextureUnitState(p.getId().toStdString()+"_texEyes");

                 //texture2->setColourOperationEx(Ogre::LBO_MODULATE,Ogre::LBS_TEXTURE,Ogre::LBS_MANUAL,Ogre::ColourValue::White,Ogre::ColourValue(1,0,0,1));


             cube->setMaterialName(p.getId().toStdString()+"_mat");*/




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

             //Update HUD
             playerHUDMgt->setLife(p.getLife());
             playerHUDMgt->setKillsValue(p.getKills());
             playerHUDMgt->setDeathValue(p.getDeaths());
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
