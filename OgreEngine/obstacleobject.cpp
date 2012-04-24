#include "obstacleobject.h"

ObstacleObject::ObstacleObject(Ogre::SceneManager * sceneMgr, Ogre::Vector3 size, QString id, Ogre::ColourValue color, Ogre::Vector3 position, Ogre::SceneNode * parentNode ):
    Object::Object( sceneMgr, 100, id, parentNode)
{
    initObstacle(id, position, size, color);
}

ObstacleObject::ObstacleObject(Ogre::SceneManager * sceneMgr, Obstacles p):
    Object::Object( sceneMgr, 100, p.getId())
{
    float r;
    float g;
    float b;
    p.getColor(&r,&g,&b);
    initObstacle(p.getId(), Ogre::Vector3(p.getX(),p.getY(),p.getZ()), Ogre::Vector3(p.getWidth(),p.getHeight(),p.getLength()), Ogre::ColourValue(r,g,b));
}

void ObstacleObject::initObstacle(QString id, Ogre::Vector3 position, Ogre::Vector3 objectSize, Ogre::ColourValue color){
    entity = mSceneMgr->createEntity(id.toStdString(), "Prefab_Cube");
    node->setPosition(position);

    //Set the color
    material = Ogre::MaterialManager::getSingleton().create(id.toStdString() +"_mat", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    entity->setMaterial(material);
    material->setDiffuse(Ogre::ColourValue(1,0,0,1));

    ((Ogre::SceneNode*)node)->attachObject(entity);

    material->setDiffuse(color);
    material->setAmbient(color);

    this->color = color;

    setScale(objectSize);
}
Ogre::SceneNode * ObstacleObject::getNode(){
    return node;
}

void ObstacleObject::setColor(float r, float g, float b){
    if(color.r != r || color.g != g || color.b != b){
        color.r = r;
        color.g = g;
        color.b = b;
        material->setDiffuse(color);
        material->setAmbient(color);
    }
}

void ObstacleObject::updateState(Obstacles &p){
    //Ogre::ColourValue color;
    //p.getColor(color.r,color.g,color.b);
    //setColor(color.r,color.g,color.b);
    setScale(Ogre::Vector3(p.getWidth(),p.getHeight(),p.getLength()));
    setPosition(p.getX(),p.getY(),p.getZ());
}

ObstacleObject::~ObstacleObject(){
    Ogre::MaterialManager::getSingleton().remove((Ogre::ResourcePtr&)material);
    mSceneMgr->destroyEntity(entity);
}

