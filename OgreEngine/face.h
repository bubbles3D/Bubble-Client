#ifndef FACE_H
#define FACE_H
#include "OGRE/Ogre.h"
#include "environnement.h"
#include <QString>


class Face{
public:

Face(Ogre::SceneManager * sceneManager, QString faceName, QString textureName, Ogre::Real size, side mside );
void setSide(side sid);
void setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z);
void setDiffuse(Ogre::Real r, Ogre::Real g, Ogre::Real b, Ogre::Real a);
void setAmbient(Ogre::Real r, Ogre::Real g, Ogre::Real b);
void setImageScale(Ogre::Real scale);
void setImage(Ogre::Real scale, QString textureName);

protected:
 Ogre::SceneManager * mSceneManager;
 Ogre::SceneNode * mNode;
 Ogre::Entity * mEntity;
 Ogre::MaterialPtr mMaterial;

 Ogre::Real mSize;
 Ogre::Real mImageScale;

 QString textureName;
 Ogre::TextureUnitState* tuisTexture;

 Ogre::MovablePlane * mfaceDir;
 side mSide;
};

#endif // FACE_H