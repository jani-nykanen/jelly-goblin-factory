// Scene manager
// (c) 2019 Jani Nykänen

#ifndef __SCENE_MAN_H__
#define __SCENE_MAN_H__

#include <vector>
#include <string>
#include <cstdlib>

#include "Scene.hpp"

// Scene manager
class SceneManager {

private:
    
    // Scenes
    std::vector<Scene*> scenes;
    // Global scene
    Scene* globalScene;
    // Active scene
    Scene* activeScene;

    // References
    EventManager* evMan;
    AssetPack* assets;

public:
    
    // Constructor
    SceneManager(EventManager* evMan, AssetPack* assets);
    // Destructor
    ~SceneManager();

    // Add a scene
    void addScene(Scene* s, bool makeActive=false, bool makeGlobal=false);
    // Change active scene
    void changeActiveScene(std::string name, void* param=NULL);

    // Initialize scenes
    void init();
    // Update scenes
    void update(float tm);
    // Draw scenes
    void draw(Graphics* g);

    // Dispose scenes
    void dispose();

};


// Scene info
struct SceneInfo {

    Scene* s;
    bool makeGlobal;
    bool makeActive;

    // Constructors
    inline SceneInfo() {}
    inline SceneInfo(Scene*s) {

        this->s = s;
        makeActive = false;
        makeGlobal = false;
    }
    inline SceneInfo(Scene*s, bool makeActive) {

        this->s = s;
        makeActive = makeActive;
        this->makeGlobal = false;
    }
    inline SceneInfo(Scene*s, bool makeActive, bool makeGlobal) {

        this->s = s;
        this->makeActive = makeActive;
        this->makeGlobal = makeGlobal;
    }
};


#endif // __SCENE_MAN_H__
