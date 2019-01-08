// Scene
// (c) 2019 Jani Nykänen

#ifndef __SCENE_H__
#define __SCENE_H__

#include <string>

#include "EventManager.hpp"
#include "Graphics.hpp"
#include "AssetPack.hpp"

class SceneManager;

// Scene class
class Scene {

protected:

    // Event manager reference
    EventManager* evMan;
    // Scene manager reference
    SceneManager* sceneMan;
    // Global asset pack
    AssetPack* assets;

public:

    // Set references
    void setReferences(EventManager* evMan, 
        SceneManager* sceneMan, 
        AssetPack* assets);

    // Methods
    virtual void init() {}
    virtual void update(float tm) {}
    virtual void draw(Graphics* g) {}
    virtual void dispose() {}
    virtual void onChange() {}
    virtual std::string getName() =0;

};

#endif // __SCENE_H__
