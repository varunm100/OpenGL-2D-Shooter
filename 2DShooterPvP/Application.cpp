#include "Game.h"

int main() {
    Game game(1920, 1080, "LMAO... its a game", false);
    
    game.InitGameData();
    game.RunMainGameLoop();

    return 0;
}