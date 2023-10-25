#include "Game.h"

int main() {
    Game* game = Game::getInstance();
    while (game->getCurrentTurn() < 10) {
        game->getInfo();
        game->playTurn();
        game->nextTurn();
    }

    return 0;
}