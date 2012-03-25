#include "cube.h"

Cube::Cube(float dim, Ogre::SceneManager * mSceneMgr,QString imageName, float imageScale, Ogre::ColourValue bot,Ogre::ColourValue top,Ogre::ColourValue x,Ogre::ColourValue xop,Ogre::ColourValue z,Ogre::ColourValue zop):
    botFace(Face(mSceneMgr, "BotFace", imageName, dim, BOTTOM)),
    topFace(Face(mSceneMgr, "top", imageName, dim, TOP)),
    xFace(Face(mSceneMgr, "x", imageName, dim, XSIDE)),
    xOpFace(Face(mSceneMgr, "xOP", imageName, dim, XSIDE_OP)),
    zFace(Face(mSceneMgr, "z", imageName, dim, ZSIDE)),
    zOpFace(Face(mSceneMgr, "zop", imageName, dim, ZSIDE_OP))
{

    mainLight = mSceneMgr->createLight("Centerlight");
    mainLight->setPosition(dim/2,dim/2,dim/2);

    cornerLight = mSceneMgr->createLight("Cornerlight");
    cornerLight->setPosition(0,0,0);
    cornerLight->setPowerScale(0.5);

    cornerOpLight = mSceneMgr->createLight("CornerlightOP");
    cornerOpLight->setPosition(dim,dim,dim);
    cornerOpLight->setPowerScale(0.5);

    //Plan bot
    //botFace = Face(mSceneMgr, "BotFace", imageName, dim, BOTTOM);
    botFace.setPosition(dim/2,0,dim/2);
    botFace.setDiffuse(bot.r,bot.g,bot.b,bot.a);
    botFace.setAmbient(bot.r,bot.g,bot.b);
    botFace.setImageScale(imageScale);

    //Plan top
    //topFace = Face(mSceneMgr, "top", "Croix.png", dim, TOP);
    topFace.setPosition(dim/2,dim,dim/2);
    topFace.setDiffuse(top.r,top.g,top.b,top.a);
    topFace.setAmbient(top.r,top.g,top.b);
    topFace.setImageScale(imageScale);

    //Plan zop
    //zOpFace = Face(mSceneMgr, "zop", imageName, dim, ZSIDE_OP);
    zOpFace.setPosition(dim,dim/2,dim/2);
    zOpFace.setDiffuse(zop.r,zop.g,zop.b,zop.a);
    zOpFace.setAmbient(zop.r,zop.g,zop.b);
    zOpFace.setImageScale(imageScale);

    //Plan z
    //zFace = Face(mSceneMgr, "z", imageName, dim, ZSIDE);
    zFace.setPosition(0,dim/2,dim/2);
    zFace.setDiffuse(z.r,z.g,z.b,z.a);
    zFace.setAmbient(z.r,z.g,z.b);
    zFace.setImageScale(imageScale);

    //Plan x
    //xFace = Face(mSceneMgr, "x", imageName, dim, XSIDE);
    xFace.setPosition(dim/2,dim/2,0);
    xFace.setDiffuse(x.r,x.g,x.b,x.a);
    xFace.setAmbient(x.r,x.g,x.b);
    xFace.setImageScale(imageScale);

    //Plan xOP
    //xOpFace = Face(mSceneMgr, "xOP", imageName, dim, XSIDE_OP);
    xOpFace.setPosition(dim/2,dim/2,dim);
    xOpFace.setDiffuse(xop.r,xop.g,xop.b,xop.a);
    xOpFace.setAmbient(xop.r,xop.g,xop.b);
    xOpFace.setImageScale(imageScale);
}

Face * Cube::getFace(side face){
    Face * facePtr;
    switch(face){
    case BOTTOM:
        facePtr = &botFace;
        break;
    case TOP:
        facePtr = &topFace;
        break;
    case ZSIDE:
        facePtr = &zFace;
        break;
    case ZSIDE_OP:
        facePtr = &zOpFace;
        break;
    case XSIDE:
        facePtr = &xFace;
        break;
    case XSIDE_OP:
        facePtr = &xOpFace;
        break;
    default:
        facePtr = 0;
        break;

    }
    return facePtr;
}
