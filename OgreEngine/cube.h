#ifndef CUBE_H
#define CUBE_H
#include "OGRE/Ogre.h"
#include "face.h"

class Cube{
public:
    Cube(float dim, Ogre::SceneManager * mSceneMgr,QString imageName,float imageScale = 1, Ogre::ColourValue bot = Ogre::ColourValue(1,0,0,0.5),Ogre::ColourValue top = Ogre::ColourValue(0,0,1,0.5),Ogre::ColourValue x = Ogre::ColourValue(0,1,1,0.5),Ogre::ColourValue xop = Ogre::ColourValue(1,0,1,0.5),Ogre::ColourValue z = Ogre::ColourValue(1,1,0,0.5),Ogre::ColourValue zop = Ogre::ColourValue(0,1,0,0.5));
    Face * getFace(side face);
protected:
    Face botFace;
    Face topFace;
    Face xFace;
    Face xOpFace;
    Face zFace;
    Face zOpFace;

    Ogre::Light * mainLight;
    Ogre::Light * cornerLight;
    Ogre::Light * cornerOpLight;

};

#endif // CUBE_H
