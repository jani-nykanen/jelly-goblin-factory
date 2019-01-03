// Main file
// (c) 2019 Jani Nykänen

#include "Core/Application.hpp"
#include "Scenes/Game/Game.hpp"


// Main
int main(int argc, char** argv) {

    // Scene info
    std::vector<SceneInfo> scenes = 
        std::vector<SceneInfo> ();
    // Add scenes
    scenes.push_back(SceneInfo(new Game(), true, false));

    // Run application
    return Application(&scenes).run(argc, argv);
}
