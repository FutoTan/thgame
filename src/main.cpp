#include "game/game.h"

int main(int argc, char** argv) {
    Game::GetInstance()->Execute(argc, argv);
    return 0;
}