// Ending scene
// (c) 2019 Jani Nykänen

#ifndef __ENDING_H__
#define __ENDING_H__

#include "../../Core/Scene.hpp"

#include "../../Core/Transition.hpp"

// Ending class
class Ending : public Scene {

private:

    // Bitmaps
    Bitmap* bmpFont;
    Bitmap* bmpTrophy;
    // Samples
    Sample* sAccept;

    // Transition
    Transition* trans;

    // Completion mode
    int complMode;
    // Ending timer
    float endingTimer;

    // Ending texts
    std::string endingText[2];

public:

    // Back to stage menu
    void back();

    // Initialize scene
    void init();
    // Update scene
    void update(float tm);
    // Draw scene
    void draw(Graphics* g);
    // Destroy scene
    void dispose();
    // On change
    void onChange(void* param=NULL);

    // Get name
    inline std::string getName() {
        return "ending";
    }

};

#endif // __ENDING_H__
