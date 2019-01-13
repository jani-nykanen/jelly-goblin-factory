// Scene manager
// (c) 2019 Jani Nykänen

#include "SceneManager.hpp"

#include <cstdio>


// Constructor
SceneManager::SceneManager(EventManager* evMan, AssetPack* assets) {

    // Store references
    this->evMan = evMan;
    this->assets = assets;

    // Initialize data
    scenes = std::vector<Scene*> ();
    activeScene = NULL;
    globalScene = NULL;
}


// Destructor
SceneManager::~SceneManager() {

    for(int i = 0; i < scenes.size(); ++ i) {

        delete scenes[i];
    }
}


// Add a scene
void SceneManager::addScene(Scene* s, bool makeActive, bool makeGlobal) {

    s->setReferences(evMan, this, assets);
    scenes.push_back(s);

    if(makeActive)
        activeScene = s;
    
    if(makeGlobal)
        globalScene = s;
}


// Change active scene
void SceneManager::changeActiveScene(std::string name) {
    
    // Go through the scenes and try to find a
    // corresponding scene
    Scene* s = NULL;
    for(int i = 0; i < scenes.size(); ++ i) {

        if(scenes[i]->getName() == name) {

            s = scenes[i];
            break;
        }
    }
    if(s == NULL) return;

    // Change scene
    s->onChange();
    activeScene = s;
}


// Initialize scenes
void SceneManager::init() {

    for(int i = 0; i < scenes.size(); ++ i) {

        scenes[i]->init();
    }
}


// Update scenes
void SceneManager::update(float tm) {

    if(globalScene != NULL)
        globalScene->update(tm);

    if(activeScene != NULL)
        activeScene->update(tm);
}


// Draw scenes
void SceneManager::draw(Graphics* g){

    if(activeScene != NULL)
        activeScene->draw(g);

    if(globalScene != NULL)
        globalScene->draw(g);
}


// Dispose scenes
void SceneManager::dispose() {

    for(int i = 0; i < scenes.size(); ++ i) {

        scenes[i]->dispose();
    }
}
