// Game scene
// (c) 2019 Jani Nykänen

#include "../../Core/Scene.hpp"

// Game scene
class Game : public Scene {

private:

    // ...

public:

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
    
    // Get name
    inline std::string getName() {

        return "game";
    }
};
