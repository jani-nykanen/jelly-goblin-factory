// Main file
// (c) 2019 Jani Nykänen

#include "Core/Application.hpp"
#include "Scenes/Game/Game.hpp"
#include "Scenes/StageMenu/StageMenu.hpp"
#include "Scenes/Ending/Ending.hpp"
#include "Scenes/Global.hpp"


// Main
int main(int argc, char** argv) {

    // Scene info
    std::vector<SceneInfo> scenes = 
        std::vector<SceneInfo> ();
    // Add scenes
    scenes.push_back(SceneInfo(new Global(), false, true));
    scenes.push_back(SceneInfo(new Game()));
    scenes.push_back(SceneInfo(new Ending()));
    scenes.push_back(SceneInfo(new StageMenu(), true, false));

    // Run application
    return Application("app.cfg", scenes).run(argc, argv);
}
