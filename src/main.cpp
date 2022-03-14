#include <iostream>

#include "fsgs.hpp"

int main(int argc, char** argv)
{
    try {
        FSGS::Game game;
        game.mainLoop();
    } catch (FSGS::Exception& e) {
        std::cerr << "Error: " << e.getError() << "\n";
        std::cerr << e.getMessage() << "\n";
    }

    return 0;
}