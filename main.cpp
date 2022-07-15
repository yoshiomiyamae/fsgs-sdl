#include <iostream>

#include "fsgs.hpp"

int main(int argc, char **argv)
{
    FSGS::Game game;
    try
    {
        game.mainLoop();
    }
    catch (FSGS::Exception &e)
    {
        std::cerr << "Error: " << e.getError() << std::endl;
        std::cerr << e.getMessage() << std::endl;
        std::cerr << game.getSdlError() << std::endl;
    }

    return 0;
}