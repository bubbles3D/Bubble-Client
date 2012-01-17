#include "App.h"

using namespace Ogre;

//-------------------------------------------------------------------------------------
Application::Application(void)
{

}
//-------------------------------------------------------------------------------------
Application::~Application(void)
{

}

//-------------------------------------------------------------------------------------
void Application::createScene(void)
{
    // Set ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);

    MeshManager::getSingleton();

    // Set camera look point
    mCamera->setPosition(40, 100, 580);
    mCamera->pitch(Ogre::Degree(-30));
    mCamera->yaw(Ogre::Degree(-45));

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

}


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
        // Create application object
        Application app;

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

