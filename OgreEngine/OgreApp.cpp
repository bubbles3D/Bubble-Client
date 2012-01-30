#include "OgreApp.h"

using namespace Ogre;

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
    // Set ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);

    MeshManager::getSingleton();

    // Set camera look point
    mCamera->setPosition(40, 100, 580);
    mCamera->pitch(Ogre::Degree(0));
    mCamera->yaw(Ogre::Degree(0));
    setupViewport(mSceneMgr,mCamera->getName());

    //Initialise playerCamera
    playerCamera = mSceneMgr->createCamera("playerCamera");
    mRotateSpeed = .1;

    //Scene
    Ogre::Entity* cube = mSceneMgr->createEntity("cube", "BoxTest.mesh");
    Ogre::SceneNode* cubeNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    cubeNode->setPosition(0,55,0);
    cubeNode->attachObject(cube);

    Ogre::Entity* plan = mSceneMgr->createEntity("plano", "Plane.mesh");
    Ogre::SceneNode* planNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    planNode->setPosition(0,0,0);

    planNode->attachObject(plan);

    // Create a light
    Ogre::Light* l = mSceneMgr->createLight("MainLight");
    l->setPosition(20,80,50);

    //Init mode
    mode = FREE;

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

    mTrayMgr->frameRenderingQueued(evt);

    if (!mTrayMgr->isDialogVisible())
    {
        mCameraMan->frameRenderingQueued(evt);   // if dialog isn't up, then update the camera
        if (mDetailsPanel->isVisible())   // if details panel is visible, then update its contents
        {
            mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(mCamera->getDerivedPosition().x));
            mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(mCamera->getDerivedPosition().y));
            mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(mCamera->getDerivedPosition().z));
            mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().w));
            mDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().x));
            mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().y));
            mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().z));
        }
    }

    updatePositions();

    return true;
}
//-------------------------------------------------------------------------------------
bool OgreApp::keyPressed( const OIS::KeyEvent &arg )
{
    if (mTrayMgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up

    if (arg.key == OIS::KC_F)   // toggle visibility of advanced frame stats
    {
        mTrayMgr->toggleAdvancedFrameStats();
    }
    else if (arg.key == OIS::KC_G)   // toggle visibility of even rarer debugging details
    {
        if (mDetailsPanel->getTrayLocation() == OgreBites::TL_NONE)
        {
            mTrayMgr->moveWidgetToTray(mDetailsPanel, OgreBites::TL_TOPRIGHT, 0);
            mDetailsPanel->show();
        }
        else
        {
            mTrayMgr->removeWidgetFromTray(mDetailsPanel);
            mDetailsPanel->hide();
        }
    }
    else if (arg.key == OIS::KC_T)   // cycle polygon rendering mode
    {
        Ogre::String newVal;
        Ogre::TextureFilterOptions tfo;
        unsigned int aniso;

        switch (mDetailsPanel->getParamValue(9).asUTF8()[0])
        {
        case 'B':
            newVal = "Trilinear";
            tfo = Ogre::TFO_TRILINEAR;
            aniso = 1;
            break;
        case 'T':
            newVal = "Anisotropic";
            tfo = Ogre::TFO_ANISOTROPIC;
            aniso = 8;
            break;
        case 'A':
            newVal = "None";
            tfo = Ogre::TFO_NONE;
            aniso = 1;
            break;
        default:
            newVal = "Bilinear";
            tfo = Ogre::TFO_BILINEAR;
            aniso = 1;
        }

        Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
        Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
        mDetailsPanel->setParamValue(9, newVal);
    }
    else if (arg.key == OIS::KC_R)   // cycle polygon rendering mode
    {
        Ogre::String newVal;
        Ogre::PolygonMode pm;

        switch (mCamera->getPolygonMode())
        {
        case Ogre::PM_SOLID:
            newVal = "Wireframe";
            pm = Ogre::PM_WIREFRAME;
            break;
        case Ogre::PM_WIREFRAME:
            newVal = "Points";
            pm = Ogre::PM_POINTS;
            break;
        default:
            newVal = "Solid";
            pm = Ogre::PM_SOLID;
        }

        mCamera->setPolygonMode(pm);
        mDetailsPanel->setParamValue(10, newVal);
    }
    else if(arg.key == OIS::KC_F5)   // refresh all textures
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
         case OIS::KC_F3 :
            mode = FREE;
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
    }






    return true;
}

bool OgreApp::mouseMoved( const OIS::MouseEvent &arg )
{
    //if (mTrayMgr->injectMouseMove(arg)) return true;

    switch(mode){
    case FREE:
        mCameraMan->injectMouseMove(arg);
             break;
    case FIRST:
        playerCameraNode->yaw(Ogre::Degree(-arg.state.X.rel * mRotateSpeed));
        playerNode->pitch(Ogre::Degree(-arg.state.Y.rel * mRotateSpeed));
             break;
    }

    return true;
}

bool OgreApp::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if (mTrayMgr->injectMouseDown(arg, id)) return true;
    mCameraMan->injectMouseDown(arg, id);
    return true;
}

bool OgreApp::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if (mTrayMgr->injectMouseUp(arg, id)) return true;
    mCameraMan->injectMouseUp(arg, id);
    return true;
}

 void OgreApp::run(){
     BaseApplication::go();
 }

 void OgreApp::updatePositions(){
     Model * model = Model::getInstance();
     QList<Player> playerList = model->getUpdatedPlayers();

     //Update elements position
     foreach(Player p, playerList){

         Ogre::Node* node;
         try{
             //MAJ position des joueurs
             node = mSceneMgr->getRootSceneNode()->getChild(p.getName().toStdString());
             node->setPosition(p.getX(),55,p.getZ());
         }catch (Ogre::Exception ex){
             //Si le joueur n'existe pas
             Ogre::Entity* cube = mSceneMgr->createEntity(p.getName().toStdString(), "Bubble-Gum.mesh");
             Ogre::SceneNode* cubeNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(p.getName().toStdString());
             cubeNode->setPosition(p.getX(),55,p.getZ());
             cubeNode->scale(20,20,20);

             if(model->getName() == p.getName()){
                 //Si c'est notre joueur
                 playerCameraNode = cubeNode->createChildSceneNode(p.getName().toStdString() + "_cam", Ogre::Vector3(0,0,1));
                 playerCameraNode->attachObject(playerCamera);
                 cubeNode->setVisible(false,true);
                 playerCamera->rotate(Ogre::Vector3(0,1,0), Ogre::Angle(180));
                 setupViewport(mSceneMgr,playerCamera->getName());
                 playerNode = cubeNode;
                 mode = FIRST;
             }

             cubeNode->attachObject(cube);
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
