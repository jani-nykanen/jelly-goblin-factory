// Handles communication between
// "Game" class and its components
// (c) 2019 Jani Nykänen

#include "Communicator.hpp"

#include "Game.hpp"

// Add a worker
void Communicator::addWorker(Point p, int color, 
        bool sleeping, bool isCog) {

    gameRef->addWorker(p, color, sleeping, isCog);
}


// Draw workers
void Communicator::drawWorkers(Graphics* g) {

    gameRef->drawWorkers(g);
}
