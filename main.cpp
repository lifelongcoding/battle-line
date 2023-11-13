#include "Game.h"
#include "Deck.h"
#include "TroopCardPile.h"
#include "Region.h"

int main() {
    Game* game = Game::getInstance();
    game->init();
    while (true) {
        game->getInfo();
        game->playTurn();

        if (game->isGameOver()) {
            std::cout << game->getAnotherPlayer().getName() << "Win!";
            break;
        }

        game->nextTurn();
    }

    return 0;
}