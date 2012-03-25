#include "face.h"

Face::Face(Ogre::SceneManager * sceneManager, QString faceName, QString texName, Ogre::Real size, side mside ):
    textureName(texName)
{
    mSceneManager = sceneManager;
    mNode = mSceneManager->getRootSceneNode()->createChildSceneNode();

    mSize = size;
    mSide = mside;

    mImageScale = 1; //Default

    //Set the plane initiale orientation
    mfaceDir = new Ogre::MovablePlane(faceName.toStdString() + "_dir");
    mfaceDir->d = 0;
    mfaceDir->normal = Ogre::Vector3::UNIT_Y;

    //Create the mesh
    Ogre::MeshManager::getSingleton().createPlane(faceName.toStdString()+"_mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, *mfaceDir, mSize ,mSize, 1, 1, true, 1, 1, 1, Ogre::Vector3::UNIT_Z);
    mEntity = mSceneManager->createEntity(faceName.toStdString()+"_entity", faceName.toStdString()+"_mesh");
    mMaterial = Ogre::MaterialManager::getSingleton().create(faceName.toStdString()+"_mat", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    if(textureName != 0){
        tuisTexture = mMaterial->getTechnique(0)->getPass(0)->createTextureUnitState(textureName.toStdString());
        tuisTexture->setTextureScale(mImageScale,mImageScale);
    }

    mEntity->setMaterialName(faceName.toStdString()+"_mat");

    mNode->attachObject(mEntity);
    mNode->setPosition(0,0,0);

    setSide(mSide);
}

void Face::setImageScale(Ogre::Real scale){
    if(textureName != 0){
        tuisTexture->setTextureScale(scale,scale);
    }

}

void Face::setImage(Ogre::Real scale, QString texName){
     textureName = texName;
     tuisTexture = mMaterial->getTechnique(0)->getPass(0)->createTextureUnitState(textureName.toStdString());
     tuisTexture->setTextureScale(scale,scale);
}

void Face::setSide(side sid){
    mNode->setOrientation(mNode->getInitialOrientation());
    switch(sid){
    case BOTTOM:
                break;
    case TOP:
        mNode->roll(Ogre::Degree(180));
                break;
    case ZSIDE:
        mNode->roll(Ogre::Degree(-90));
                break;
    case ZSIDE_OP:
        mNode->roll(Ogre::Degree(+90));
                break;
    case XSIDE:
        mNode->pitch(Ogre::Degree(90));
                break;
    case XSIDE_OP:
        mNode->pitch(Ogre::Degree(-90));
                break;
    }
}
void Face::setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z){
    mNode->setPosition(x,y,z);
}

void Face::setDiffuse(Ogre::Real r, Ogre::Real g, Ogre::Real b, Ogre::Real a){
    mMaterial->setDiffuse(r, g, b, a);
    //mMaterial->setAmbient(0.0, 0, 1.0);
}

void Face::setAmbient(Ogre::Real r, Ogre::Real g, Ogre::Real b){
    mMaterial->setAmbient(r, g, b);
}

