// Main file
// (c) 2019 Jani Nykänen

#include "Core/Application.hpp"
#include "Scenes/Game/Game.hpp"
#include "Scenes/Global.hpp"


// Main
int main(int argc, char** argv) {

    // Scene info
    std::vector<SceneInfo> scenes = 
        std::vector<SceneInfo> ();
    // Add scenes
    scenes.push_back(SceneInfo(new Global(), false, true));
    scenes.push_back(SceneInfo(new Game(), true, false));

    // Run application
    Application* app = new Application("app.cfg", &scenes);
    int ret = app->run(argc, argv);
    // TODO: Might cause problems?
    if(ret == 0) {

        delete app;
    }
    return ret;
}
