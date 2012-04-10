#include "bulletobject.h"

BulletObject::BulletObject(Ogre::SceneManager * sceneMgr, float size, QString id, Ogre::ColourValue color, Ogre::Vector3 position):
    Object::Object( sceneMgr, 100, id)
{
    initBullet(id, position, size, color);

}

BulletObject::BulletObject(Ogre::SceneManager * sceneMgr, Bullet p):
    Object::Object( sceneMgr, 100, p.getId())
{
    float r;
    float g;
    float b;
    p.getColor(&r,&g,&b);
    initBullet(p.getId(), Ogre::Vector3(p.getX(),p.getY(),p.getZ()), p.getHeight(), Ogre::ColourValue(r,g,b));
}

void BulletObject::initBullet(QString id, Ogre::Vector3 position, float objectSize, Ogre::ColourValue color){
    entity = mSceneMgr->createEntity(id.toStdString(), "Prefab_Sphere");
    node->setPosition(position);

    //Set the color
    material = Ogre::MaterialManager::getSingleton().create(id.toStdString() +"_mat", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    entity->setMaterial(material);
    material->setDiffuse(Ogre::ColourValue(1,0,0,1));

    ((Ogre::SceneNode*)node)->attachObject(entity);
    material->setDepthWriteEnabled(false);
    material->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    material->setSelfIllumination(Ogre::ColourValue(color.r,color.g,color.b));
    material->setDiffuse(Ogre::ColourValue(0,0,0,color.a));
    material->setSpecular(Ogre::ColourValue(0,0,0,0));
    material->setAmbient(Ogre::ColourValue(0,0,0,0));
    this->color = color;

    setScale(objectSize);
}
void BulletObject::setColor(float r, float g, float b){
    if(color.r != r || color.g != g || color.b != b){

        color.r = r;
        color.g = g;
        color.b = b;
        material->setSelfIllumination(color);
    }
}

void BulletObject::updateState(Bullet &p){
    float r;
    float g;
    float b;
    p.getColor(&r,&g,&b);
    setColor(r,g,b);
    setScale(Ogre::Vector3(p.getWidth(),p.getHeight(),p.getLength()));
    setPosition(p.getX(),p.getY(),p.getZ());
}

BulletObject::~BulletObject(){
    Ogre::MaterialManager::getSingleton().remove((Ogre::ResourcePtr&)material);
    mSceneMgr->destroyEntity(entity);
}
