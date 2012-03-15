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

    /*
    ////
    Ogre::Entity* plan = mSceneMgr->createEntity("plano", "Plane.mesh");
    Ogre::SceneNode* planNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    //Ogre::Mesh *pMesh = plan->getMesh().getPointer();
    planNode->setPosition(0,0,0);
    //Ogre::Material *pMaterial = (Ogre::Material *) Ogre::MaterialManager::getSingleton().getByName(((pMesh->getSubMesh(0))->getMaterialName()));

    //Ogre::TextureUnitState *pTex = pMaterial->getBestTechnique(0)->createPass()->createTextureUnitState();
   //pTex->setColourOperationEx(LBX_BLEND_DIFFUSE_COLOUR, LBS_MANUAL, LBS_CURRENT, ColourValue::Red);
   //pMaterial->setSceneBlending(SBT_TRANSPARENT_COLOUR);

   Ogre::MaterialPtr m_pMat = plan->getSubEntity(0)->getMaterial();
   m_pMat->getTechnique(0)->getPass(0)->setAmbient(1, 0, 0);
   m_pMat->getTechnique(0)->getPass(0)->setDiffuse(1, 1, 0, 0);
   plan->setMaterialName(m_pMat->getName());
    /////
*/

    ////
    createCube();

    //planNode->attachObject(plan);

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

    //Set up the scene
    Model *model = Model::getInstance();
    updateObjectsPositions("Cube.mesh", model->getUpdatedObstacles());

    //Test
    plane = BOTTOM;

    //Plan x
    /*
    Ogre::Entity* planX = mSceneMgr->createEntity("planoX", "Plane.mesh");
    Ogre::SceneNode* planNodeX = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    planNodeX->setPosition(3000,1500,1500);
    planNodeX->roll(Ogre::Degree(90));
    planNodeX->attachObject(planX);
    */
}

void OgreApp::createCube(){
    Model *model = Model::getInstance();
    float dim = model->getMapLength();


    //Plan x
    Ogre::Entity* planB = mSceneMgr->createEntity("planoB", "Plane.mesh");
    Ogre::SceneNode* planNodeB = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    float realDim = Utils::getEdgeLength2D(planB);
    planNodeB->setPosition(dim/2,0,dim/2);
    //planNodeX->roll(Ogre::Degree(90));
    Real ratio = dim/realDim;
    planNodeB->attachObject(planB);
    qDebug()<<"DIM: "<<ratio;
    planNodeB->scale(ratio*1.02,0,ratio*1.02);

    //Plan zop
    planB = mSceneMgr->createEntity("planoZOP", "Plane.mesh");
    planNodeB = mSceneMgr->getRootSceneNode()->createChildSceneNode();

    planNodeB->setPosition(dim,dim/2,dim/2);
    planNodeB->roll(Ogre::Degree(90));
    planNodeB->attachObject(planB);
    qDebug()<<"DIMzop: "<<ratio;
    planNodeB->scale(ratio*1.02,0,ratio*1.02);

    //Plan top
    planB = mSceneMgr->createEntity("planoTOP", "Plane.mesh");
    planNodeB = mSceneMgr->getRootSceneNode()->createChildSceneNode();

    planNodeB->setPosition(dim/2,dim,dim/2);
    planNodeB->roll(Ogre::Degree(180));
    planNodeB->attachObject(planB);
    qDebug()<<"DIMtop: "<<realDim;
    planNodeB->scale(ratio*1.02,0,ratio *1.02);

    //Plan z
    planB = mSceneMgr->createEntity("planoZ", "Plane.mesh");
    planNodeB = mSceneMgr->getRootSceneNode()->createChildSceneNode();

    planNodeB->setPosition(0,dim/2,dim/2);
    planNodeB->roll(Ogre::Degree(-90));
    planNodeB->attachObject(planB);
    qDebug()<<"DIMz: "<<realDim;
    planNodeB->scale(ratio*1.02,0,ratio *1.02);

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
        playerNode->setOrientation(playerNode->getInitialOrientation());
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

    switch(mode){
    case FREE:
        mCameraMan->injectMouseMove(arg);

             break;
    case FIRST: 

        playerCameraNode->pitch(Ogre::Degree(+arg.state.Y.rel * mRotateSpeed));
        playerRotationNode->yaw(Ogre::Degree(-arg.state.X.rel * mRotateSpeed));

        //Transmit to server
        mod->updateMouse(playerTargetNode->_getDerivedPosition().x - playerNode->_getDerivedPosition().x,playerTargetNode->_getDerivedPosition().y - playerNode->_getDerivedPosition().y,playerTargetNode->_getDerivedPosition().z - playerNode->_getDerivedPosition().z);

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
         Ogre::Node* rotNode;
         Ogre::Node* entityNode;

         try{
             //MAJ position des joueurs
             node = mSceneMgr->getRootSceneNode()->getChild(p.getId().toStdString());
             //MAJ orientation des joueurs
             rotNode = node->getChild(p.getId().toStdString()+"_rot");
             cameraNode = rotNode->getChild(p.getId().toStdString()+"_cam");
             entityNode = cameraNode->getChild(p.getId().toStdString()+"_entity");

         }catch (Ogre::Exception ex){
             //Si le joueur n'existe pas
             qDebug()<<"Creating players";
             Ogre::Entity* cube = mSceneMgr->createEntity(p.getId().toStdString(), "Bubble-Gum-Anim.mesh");
             node = mSceneMgr->getRootSceneNode()->createChildSceneNode(p.getId().toStdString());
             node->scale(20,20,20);
             rotNode = ((Ogre::SceneNode*)node)->createChildSceneNode(p.getId().toStdString() + "_rot", Ogre::Vector3(0,0,0));
             cameraNode = ((Ogre::SceneNode*)rotNode)->createChildSceneNode(p.getId().toStdString() + "_cam", Ogre::Vector3(0,0,0));
             entityNode = ((Ogre::SceneNode*)cameraNode)->createChildSceneNode(p.getId().toStdString() + "_entity", Ogre::Vector3(0,0,0));

             if(model->getName() == p.getName()){
                 //Si c'est notre joueur
                 playerEntityNode = ((Ogre::SceneNode*)entityNode);
                 playerCameraNode = ((Ogre::SceneNode*)cameraNode);
                 playerRotationNode = ((Ogre::SceneNode*)rotNode);
                 playerTargetNode = playerCameraNode->createChildSceneNode(p.getId().toStdString() + "_target", Ogre::Vector3(0,0,1));
                 playerCameraNode->attachObject(playerCamera);
                 ((Ogre::SceneNode*)node)->setVisible(false,true);
                 playerCamera->rotate(Ogre::Vector3(0,1,0), Ogre::Angle(180));
                 setupViewport(mSceneMgr,playerCamera->getName());
                 playerNode = ((Ogre::SceneNode*)node);
                 mode = FIRST;
             }
             ((Ogre::SceneNode*)entityNode)->attachObject(cube);
             qDebug()<<"Created players";
         }


         if(model->getName() != p.getName()){
            updateObjectPosition(node, cameraNode, rotNode,p);
         }else{ // us
             //qDebug()<<"Y::::::"<<p.getY();
             //Set player orientation
             switch(p.getCube()){
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
             node->setPosition(p.getX(),p.getY(),p.getZ());
         }

     }
 }

 void OgreApp::updateObjectsPositions(const char * meshName, QList<Bullet> objectsList){

     //Update elements position
     foreach(Actor p, objectsList){

         Ogre::Node* node;
         Ogre::Node* cameraNode;
         Ogre::Node* rotNode;
         Ogre::Node* entityNode;
         try{
             //Get object's nodes if they already exist
             node = mSceneMgr->getRootSceneNode()->getChild(p.getId().toStdString());
             rotNode = node->getChild(p.getId().toStdString()+"_rot");
             cameraNode = rotNode->getChild(p.getId().toStdString()+"_cam");
             entityNode = cameraNode->getChild(p.getId().toStdString()+"_entity");

         }catch (Ogre::Exception ex){
             //If the object doesn't already exist we create it
             Ogre::Entity* cube = mSceneMgr->createEntity(p.getId().toStdString(), meshName);
             node = mSceneMgr->getRootSceneNode()->createChildSceneNode(p.getId().toStdString());
             node->setPosition(p.getX(),p.getY(),p.getZ());
             //float ratio = p.getRatio();
             //node->scale(p.getWidth(),p.getHeight(),p.getLength());
             rotNode = ((Ogre::SceneNode*)node)->createChildSceneNode(p.getId().toStdString() + "_rot", Ogre::Vector3(0,0,0));
             cameraNode = ((Ogre::SceneNode*)rotNode)->createChildSceneNode(p.getId().toStdString() + "_cam", Ogre::Vector3(0,0,0));
             entityNode = ((Ogre::SceneNode*)cameraNode)->createChildSceneNode(p.getId().toStdString() + "_entity", Ogre::Vector3(0,0,0));
             ((Ogre::SceneNode*)entityNode)->attachObject(cube);
             //initScale(cube,node);
         }
         updateObjectPosition(node, cameraNode, rotNode,p);
     }
 }

 void OgreApp::updateObjectsPositions(const char * meshName, QList<Obstacles> objectsList){

     qDebug()<<"START MAP";
     //Update elements position
     foreach(Actor p, objectsList){

         qDebug()<<"NAME "<<p.getId();
         Ogre::Node* node;
         Ogre::Node* cameraNode;
         Ogre::Node* rotNode;
         Ogre::Node* entityNode;
         try{
             //Get object's nodes if they already exist
             node = mSceneMgr->getRootSceneNode()->getChild(p.getId().toStdString());
             rotNode = node->getChild(p.getId().toStdString()+"_rot");
             cameraNode = rotNode->getChild(p.getId().toStdString()+"_cam");
             entityNode = cameraNode->getChild(p.getId().toStdString()+"_entity");


         }catch (Ogre::Exception ex){
             //If the object doesn't already exist we create it
             Ogre::Entity* cube = mSceneMgr->createEntity(p.getId().toStdString(), meshName);
             node = mSceneMgr->getRootSceneNode()->createChildSceneNode(p.getId().toStdString());
             node->setPosition(p.getX(),p.getY(),p.getZ());
             //float ratio = p.getRatio();
             //node->scale(p.getWidth(),p.getHeight(),p.getLength());
             rotNode = ((Ogre::SceneNode*)node)->createChildSceneNode(p.getId().toStdString() + "_rot", Ogre::Vector3(0,0,0));
             cameraNode = ((Ogre::SceneNode*)rotNode)->createChildSceneNode(p.getId().toStdString() + "_cam", Ogre::Vector3(0,0,0));
             entityNode = ((Ogre::SceneNode*)cameraNode)->createChildSceneNode(p.getId().toStdString() + "_entity", Ogre::Vector3(0,0,0));
             ((Ogre::SceneNode*)entityNode)->attachObject(cube);
             initScale(cube,node);
         }

         updateObjectPosition(node, cameraNode, rotNode,p);

     }
     qDebug()<<"END MAP";
 }

void OgreApp::removeObjects(QList<QString> names){
    //qDebug()<<names;
    foreach(QString name, names){
        removeObject(name);
    }
}

void OgreApp::removeObject(QString p){

        Entity * entity;
        SceneNode * node;
        try{
            qDebug()<<"Start REMOVING NODE";
            entity = mSceneMgr->getEntity(p.toStdString());
            node = (SceneNode *) mSceneMgr->getRootSceneNode()->getChild(p.toStdString());
            node->removeAndDestroyAllChildren();
            mSceneMgr->destroyEntity(entity->getName());
            //mSceneMgr->destroySceneNode(parent->getName());
            qDebug()<<"End REMOVING NODE";

        }catch (Ogre::Exception ex){
          qDebug()<<"ERROR REMOVING NODE";
        }
}

 void OgreApp::updateObjectPosition(Node* node, Node* cameraNode, Node* rotNode, Actor p){
     //Now we update nodes' positions
     node->setPosition(p.getX(),p.getY(),p.getZ());
     Ogre::Vector3 directionToLookAt =Ogre::Vector3(p.getVx() ,p.getVy() ,p.getVz());

     //Which part of the cube we are
     Ogre::Vector3 directionToLookAtHorizontal = directionToLookAt;
     Ogre::Vector3 directionToLookAtVertical = directionToLookAt;
     Ogre::Vector3 srcH;
     Ogre::Vector3 srcV;
     Ogre::Vector3 srcHorizontal;
     Ogre::Vector3 srcVertical;

     srcH = rotNode->getOrientation()* Ogre::Vector3::UNIT_Z;
     srcV = cameraNode->getOrientation()* Ogre::Vector3::UNIT_Z;

     node->setOrientation(node->getInitialOrientation());

     directionToLookAtHorizontal.y = 0;
     directionToLookAtVertical.x = 0;

     switch(p.getCube()){
     case BOTTOM: //bas

         directionToLookAtVertical.z = Ogre::Math::Sqrt(directionToLookAt.z * directionToLookAt.z + directionToLookAt.x * directionToLookAt.x) ;

         break;
     case XSIDE_OP: //COTE X  OPP
         node->pitch(Ogre::Degree(90));

         directionToLookAtHorizontal.x = directionToLookAt.x;
         directionToLookAtHorizontal.z = directionToLookAt.y;

         directionToLookAtVertical.z = Ogre::Math::Sqrt(directionToLookAt.y * directionToLookAt.y + directionToLookAt.x * directionToLookAt.x) ;
         directionToLookAtVertical.y = -directionToLookAt.z;

         break;
     case XSIDE: //COTE X
         node->pitch(Ogre::Degree(-90));

         directionToLookAtHorizontal.x = directionToLookAt.x;
         directionToLookAtHorizontal.z = -directionToLookAt.y;

         directionToLookAtVertical.z = Ogre::Math::Sqrt(directionToLookAt.y * directionToLookAt.y + directionToLookAt.x * directionToLookAt.x) ;
         directionToLookAtVertical.y = directionToLookAt.z;

         break;
     case ZSIDE: //COTE Z

         node->roll(Ogre::Degree(-90));
         directionToLookAtHorizontal.x = -directionToLookAt.y;
         directionToLookAtHorizontal.z = directionToLookAt.z;

         directionToLookAtVertical.z = Ogre::Math::Sqrt(directionToLookAt.y * directionToLookAt.y + directionToLookAt.z * directionToLookAt.z) ;
         directionToLookAtVertical.y = directionToLookAt.x;

         break;
     case ZSIDE_OP:

         node->roll(Ogre::Degree(90));

         directionToLookAtHorizontal.x = directionToLookAt.y;
         directionToLookAtHorizontal.z = directionToLookAt.z;

         directionToLookAtVertical.z = Ogre::Math::Sqrt(directionToLookAt.z * directionToLookAt.z + directionToLookAt.y * directionToLookAt.y) ;
         directionToLookAtVertical.y = -directionToLookAt.x;

         break;
     case TOP:

         node->roll(Ogre::Degree(180));

         directionToLookAtHorizontal.x = -directionToLookAt.x;
         directionToLookAtHorizontal.z = directionToLookAt.z;

         directionToLookAtVertical.z = Ogre::Math::Sqrt(directionToLookAt.z * directionToLookAt.z + directionToLookAt.x * directionToLookAt.x) ;
         directionToLookAtVertical.y = -directionToLookAt.y;

         break;
     }

     // Normalise
     directionToLookAtHorizontal.normalise();
     directionToLookAtVertical.normalise();

     srcHorizontal = srcH;
     srcHorizontal.y = 0;
     srcHorizontal.normalise();

     srcVertical = srcV;
     srcVertical.x = 0;
     srcVertical.normalise();

     //Rotation laterale
     if ((1.0f + srcHorizontal.dotProduct(directionToLookAtHorizontal)) < 0.0001f)
     {
      rotNode->yaw(Ogre::Degree(180));
     }
     else
     {
      Ogre::Quaternion quat = srcHorizontal.getRotationTo(directionToLookAtHorizontal, Ogre::Vector3::UNIT_Y);
     node->yaw(quat.getYaw());
     }
     //Rotation verticale
     if ((1.0f + srcVertical.dotProduct(directionToLookAtVertical)) < 0.0001f)
     {
      cameraNode->pitch(Ogre::Degree(180));
     }
     else
     {
      Ogre::Quaternion quat = srcVertical.getRotationTo(directionToLookAtVertical, Ogre::Vector3::UNIT_X);
      cameraNode->pitch(quat.getPitch());
     }

     //Scale
     node->setScale(p.getWidth(),p.getHeight(),p.getLength());

 }

 void OgreApp::updateObjectAnimation(Actor p, const char * animation){
     Ogre::AnimationState *animationState;
     try{
         qDebug()<<"Ogre EXception not append 1 :: ::--------------------------------------------" ;
         Ogre::Entity* entity = mSceneMgr->getEntity(p.getId().toStdString());
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
