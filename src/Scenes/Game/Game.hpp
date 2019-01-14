// Game scene
// (c) 2019 Jani Nykänen

#include "../../Core/Scene.hpp"
#include "../../Core/Bitmap.hpp"

#include "Communicator.hpp"
#include "Stage.hpp"
#include "Hud.hpp"
#include "Worker.hpp"
#include "PauseMenu.hpp"

// Game scene
class Game : public Scene {

private:

    // Bitmaps
    Bitmap* bmpFont;

    // Transition
    Transition* trans;

    // Communicator
    Communicator comm;
    // Stage
    Stage* stage;
    // Hud
    Hud hud;
    // Workers
    std::vector<Worker> workers;

    // Pause menus
    PauseMenu pause;
    PauseMenu endMenu;
    PauseMenu settings;

    // Stage clear timer
    float endTimer;

    // Draw "Stage clear"
    void drawStageClear(Graphics* g);

public:

    // Reset the current game state
    void reset();
    // Resume game
    void resume();
    // Quit
    void quit();
    // Reactivate pause
    void reactivatePause();
    // Activate settings
    void activateSettings();
    // Toggle fullscreen
    inline void toggleFullscreen() {
        evMan->toggleFullscreen();
    }
    // Toggle SFX
    void toggleSFX();
    // Toggle music
    void toggleMusic();

    // Initialize scene
    void init();
    // Update scene
    void update(float tm);
    // Draw scene
    void draw(Graphics* g);
    // Dispose scene
    void dispose();
    // Called when the scene is changed
    // to this scene
    void onChange();
    
    // Draw workers
    void drawWorkers(Graphics* g);

    // Add a worker
    void addWorker(Point p, int color, 
        bool sleeping=false, bool isCog=false);

    // Get name
    inline std::string getName() {

        return "game";
    }
};
