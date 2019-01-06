// Game scene
// (c) 2019 Jani Nykänen

#include "../../Core/Scene.hpp"
#include "../../Core/Bitmap.hpp"

// Game scene
class Game : public Scene {

private:

    // Test bitmaps
    Bitmap* bmpParrot;
    Bitmap* bmpFont;

public:

    // Initialize scene
    void init();
    // Update scene
    void update(int steps);
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
