// Handles communication between
// "Game" class and its components
// (c) 2019 Jani Nykänen

#ifndef __COMMUNICATOR_H__
#define __COMMUNICATOR_H__

#include "../../Core/Types.hpp"
#include "../../Core/Graphics.hpp"

class Game;

// Communicator class
class Communicator {

private:

    // Reference to the game scene class
    Game* gameRef;

public:

    // Constructor
    inline Communicator() {}
    inline Communicator(Game* ref) {
        gameRef = ref;
    }

    // Add a worker
    void addWorker(Point p, int color, 
        bool sleeping=false, bool isCog=false);

    // Draw workers
    void drawWorkers(Graphics* g);

};

#endif // __COMMUNICATOR_H__
