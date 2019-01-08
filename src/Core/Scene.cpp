// Scene
// (c) 2019 Jani Nykänen

#include "Scene.hpp"


// Constructor
void Scene::setReferences(EventManager* evMan, 
    SceneManager* sceneMan, 
    AssetPack* assets) {

    // Store references
    this->evMan = evMan;
    this->sceneMan = sceneMan;
    this->assets = assets;
}
