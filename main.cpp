#include "Game.h"

int main() {
    try {
        Game game;
        game.main();
    }
    catch(OutOfBoundsException& e){
        std::cout<< e.what();
    }

    return 0;
}