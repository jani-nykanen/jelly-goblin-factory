// Scene manager
// (c) 2019 Jani Nykänen

#include "SceneManager.hpp"

#include <cstdio>


// Constructor
SceneManager::SceneManager(EventManager* evMan) {

    this->evMan = evMan;

    // Initialize data
    scenes = std::vector<Scene*> ();
    activeScene = NULL;
    globalScene = NULL;
}


// Add a scene
void SceneManager::addScene(Scene* s, bool makeActive, bool makeGlobal) {

    s->setReferences(evMan, this);
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


// Dispose scenes
void SceneManager::dispose() {

    for(int i = 0; i < scenes.size(); ++ i) {

        scenes[i]->dispose();
    }
}
