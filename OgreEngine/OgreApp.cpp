#include "OgreApp.h"
#include "OGRE/Ogre.h"
#include <QDebug>


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

    //Ball
    Ogre::Entity* bullet = mSceneMgr->createEntity("ball", "Bullet.mesh");
    Ogre::SceneNode* bulletNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    bulletNode->setPosition(200,55,0);
    bulletNode->scale(40,40,40);
    bulletNode->attachObject(bullet);

    Ogre::Entity* plan = mSceneMgr->createEntity("plano", "Plane.mesh");
    Ogre::SceneNode* planNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    planNode->setPosition(0,0,0);

    planNode->attachObject(plan);

    // Create a light
    Ogre::Light* l = mSceneMgr->createLight("MainLight");
    l->setPosition(20,80,50);

    //Init mode
    mode = FREE;


    Ogre::Entity* cube41 = mSceneMgr->createEntity("cube41", "Cube.mesh");
            Ogre::SceneNode* cubeNode41 =
                            mSceneMgr->getRootSceneNode()->createChildSceneNode();
            cubeNode41->setPosition(400, 55, 0);
            cubeNode41->attachObject(cube41);
            initScale(cube41,cubeNode41);
            cubeNode41->scale(20,20,20);

            Ogre::Entity* cube74 = mSceneMgr->createEntity("ezr", "Bubble-Gum-Anim.mesh");
             qDebug()<<"BUBBLE";
              qDebug()<<Utils::getEdgeLength(cube74);

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
        switch (arg.key) {
         case OIS::KC_F1 :
                mode = FIRST;
                setupViewport(mSceneMgr,playerCamera->getName());

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

        playerCameraNode->pitch(Ogre::Degree(+arg.state.Y.rel * mRotateSpeed));
        playerNode->yaw(Ogre::Degree(-arg.state.X.rel * mRotateSpeed));
        Model * mod = Model::getInstance();
        mod->updateMouse(playerTargetNode->_getDerivedPosition().x - playerNode->_getDerivedPosition().x,playerTargetNode->_getDerivedPosition().y - playerNode->_getDerivedPosition().y,playerTargetNode->_getDerivedPosition().z - playerNode->_getDerivedPosition().z);

             break;
    }

    return true;
}

bool OgreApp::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if (mTrayMgr->injectMouseDown(arg, id)) return true;
    mCameraMan->injectMouseDown(arg, id);
    Model *mod = Model::getInstance();

    if(mode == FIRST){
        mod->shot(playerTargetNode->_getDerivedPosition().x - playerNode->_getDerivedPosition().x,playerTargetNode->_getDerivedPosition().y - playerNode->_getDerivedPosition().y,playerTargetNode->_getDerivedPosition().z - playerNode->_getDerivedPosition().z);
    }

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
     updatePlayersPositions();
     updateObjectsPositions("Bullet.mesh", model->getUpdatedBullets());

     //qDebug()<<model->getAllPlayers().length();
     //updateObjectsAnimations(model->getAllPlayers());
     removeObjects(model->getClearedActors());
 }

 void OgreApp::updatePlayersPositions(){
     Model * model = Model::getInstance();
     QList<Player> playerList = model->getUpdatedPlayers();//getAllPlayers();

     //Update elements position
     foreach(Player p, playerList){

         Ogre::Node* node;
         Ogre::Node* cameraNode;
         try{
             //MAJ position des joueurs
             node = mSceneMgr->getRootSceneNode()->getChild(p.getName().toStdString());
             //MAJ orientation des joueurs
             cameraNode = node->getChild(p.getName().toStdString()+"_cam");

         }catch (Ogre::Exception ex){
             //Si le joueur n'existe pas
             Ogre::Entity* cube = mSceneMgr->createEntity(p.getName().toStdString(), "Bubble-Gum-Anim.mesh");
             node = mSceneMgr->getRootSceneNode()->createChildSceneNode(p.getName().toStdString());
             node->scale(20,20,20);
             cameraNode = ((Ogre::SceneNode*)node)->createChildSceneNode(p.getName().toStdString() + "_cam", Ogre::Vector3(0,0,0));

             if(model->getName() == p.getName()){
                 //Si c'est notre joueur
                 playerCameraNode = ((Ogre::SceneNode*)cameraNode);
                 playerTargetNode = playerCameraNode->createChildSceneNode(p.getName().toStdString() + "_target", Ogre::Vector3(0,0,1));
                 playerCameraNode->attachObject(playerCamera);
                 ((Ogre::SceneNode*)node)->setVisible(false,true);
                 playerCamera->rotate(Ogre::Vector3(0,1,0), Ogre::Angle(180));
                 setupViewport(mSceneMgr,playerCamera->getName());
                 playerNode = ((Ogre::SceneNode*)node);
                 mode = FIRST;
             }
             ((Ogre::SceneNode*)cameraNode)->attachObject(cube);
         }


         if(model->getName() != p.getName()){
            updateObjectPosition(node,cameraNode,p);
         }else{
             node->setPosition(p.getX(),p.getY(),p.getZ());
         }

     }
 }

 void OgreApp::updateObjectsPositions(const char * meshName, QList<Bullet> objectsList){

     //Update elements position
     foreach(Actor p, objectsList){

         Ogre::Node* node;
         Ogre::Node* cameraNode;
         try{
             //Get object's nodes if they already exist
             node = mSceneMgr->getRootSceneNode()->getChild(p.getName().toStdString());
             cameraNode = node->getChild(p.getName().toStdString()+"_cam");

         }catch (Ogre::Exception ex){
             //If the object doesn't already exist we create it
             Ogre::Entity* cube = mSceneMgr->createEntity(p.getName().toStdString(), meshName);
             node = mSceneMgr->getRootSceneNode()->createChildSceneNode(p.getName().toStdString());
             node->setPosition(p.getX(),p.getY(),p.getZ());
             float ratio = p.getRatio();
             node->scale(ratio,ratio,ratio);
             cameraNode = ((Ogre::SceneNode*)node)->createChildSceneNode(p.getName().toStdString() + "_cam", Ogre::Vector3(0,0,0));
             ((Ogre::SceneNode*)cameraNode)->attachObject(cube);
         }
         updateObjectPosition(node,cameraNode,p);
     }
 }

void OgreApp::removeObjects(QList<QString> names){
    qDebug()<<names;
    foreach(QString name, names){
        removeObject(name);
    }
}

void OgreApp::removeObject(QString p){

        Entity * entity;
        try{
            entity = mSceneMgr->getEntity(p.toStdString());
            SceneNode* parent = entity->getParentSceneNode();
            parent->detachObject(entity->getName());
           // mSceneMgr->destroyEntity(entity->getName());
            //mSceneMgr->destroySceneNode(parent->getName());

        }catch (Ogre::Exception ex){
          qDebug()<<"ERROR REMOVING NODE";
        }
}
 void OgreApp::updateObjectPosition(Node* node,Node* cameraNode, Actor p){
     //Now we update nodes' positions
     node->setPosition(p.getX(),p.getY(),p.getZ());
     Ogre::Vector3 directionToLookAt =Ogre::Vector3(p.getVx() ,p.getVy() ,p.getVz());

     Ogre::Vector3 directionToLookAtHorizontal = directionToLookAt;
     directionToLookAtHorizontal.y = 0;
     directionToLookAtHorizontal.normalise();

     Ogre::Vector3 directionToLookAtVertical = directionToLookAt;
     directionToLookAtVertical.z = Ogre::Math::Sqrt(directionToLookAtVertical.z * directionToLookAtVertical.z + directionToLookAtVertical.x * directionToLookAtVertical.x) ;
     directionToLookAtVertical.x = 0;
     directionToLookAtVertical.normalise();

     Ogre::Vector3 srcH = node->getOrientation()* Ogre::Vector3::UNIT_Z;

     Ogre::Vector3 srcV = cameraNode->getOrientation()* Ogre::Vector3::UNIT_Z;

     Ogre::Vector3 srcHorizontal = srcH;
     srcHorizontal.y = 0;
     srcHorizontal.normalise();

     Ogre::Vector3 srcVertical = srcV;
     srcVertical.x = 0;
     srcVertical.normalise();

/*
     qDebug()<<"get Source direction --------------------------------------------" ;
     qDebug()<<srcV.x;
     qDebug()<<srcV.y;
     qDebug()<<srcV.z;
     qDebug()<<"end get Source direction  --------------------------------------------" ;

     qDebug()<<"get direction to look at --------------------------------------------" ;
     qDebug()<<directionToLookAt.x;
     qDebug()<<directionToLookAt.y;
     qDebug()<<directionToLookAt.z;
     qDebug()<<"get direction to look at  --------------------------------------------" ;
*/
     if ((1.0f + srcHorizontal.dotProduct(directionToLookAtHorizontal)) < 0.0001f)
     {
      node->yaw(Ogre::Degree(180));
     }
     else
     {
      Ogre::Quaternion quat = srcHorizontal.getRotationTo(directionToLookAtHorizontal, Ogre::Vector3::UNIT_Y);
     node->yaw(quat.getYaw());
     }

     if ((1.0f + srcVertical.dotProduct(directionToLookAtVertical)) < 0.0001f)
     {
      cameraNode->pitch(Ogre::Degree(180));
     }
     else
     {
      Ogre::Quaternion quat = srcVertical.getRotationTo(directionToLookAtVertical, Ogre::Vector3::UNIT_X);
      cameraNode->pitch(quat.getPitch());
     }

     float ratio = p.getRatio();
     node->setScale(ratio,ratio,ratio);
 }

 void OgreApp::updateObjectAnimation(Actor p, const char * animation){
     Ogre::AnimationState *animationState;
     try{
         qDebug()<<"Ogre EXception not append 1 :: ::--------------------------------------------" ;
         Ogre::Entity* entity = mSceneMgr->getEntity(p.getName().toStdString());
         qDebug()<<"Ogre EXception not append 2  ::- ::--------------------------------------------" ;
         animationState = entity->getAnimationState(animation);
         qDebug()<<"Ogre EXception not append 3  ::- ::--------------------------------------------" ;
         if (animationState->getEnabled() == false){
            animationState->setLoop(true);
            animationState->setEnabled(true);
         }
         animationState->addTime(0.05);

     }catch(Ogre::Exception ex){
         qDebug()<<"Ogre EXception animation ::--------------------------------------------" ;
         //qDebug()<<QString(ex.getFullDescription());
         //qDebug()<<QString((int)(ex.getLine()));
     }

 }

 void OgreApp::updateObjectsAnimations(QList<Player> objectsList){
qDebug()<<"Ogre EXception animation -1::--------------------------------------------" ;
     //Update elements position
     foreach(Actor p, objectsList){
         qDebug()<<"Ogre EXception animation -0::--------------------------------------------" ;
         updateObjectAnimation(p,"my_animation");
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

 void OgreApp::initScale(Ogre::Entity* entity, Ogre::Node * node){
     Real length = Utils::getEdgeLength(entity);
     Real ratio = 4.98725/length;



     qDebug()<<"RATIO";
     qDebug()<<ratio;
     qDebug()<<length;
     node->scale(ratio,ratio,ratio);

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
