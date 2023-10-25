#include "Game.h"


Game* Game::instance = nullptr;

void Game::playTurn() {
    Player& currentPlayer = getCurrentPlayer();

    if (!currentPlayer.hasTroopCard() || !regionsManager.canPlaceTroopCard(currentPlayer)) {
        if (currentPlayer.hasTacticsCard()) {
            int choice = InputHandler::getChoice(1, 2, "1. Play a tactics card 2. Skip");
            if (choice == 1) {
                int cardChoice = InputHandler::getChoice(1, currentPlayer.getHandsSize(), "Chose a card from hands to play: ");
                currentCard = &currentPlayer.getCard(cardChoice - 1);
                currentPlayer.playCard(cardChoice);
            } else {
                return;
            }
        } else {
            std::cout << "You have to skip this turn." << std::endl;
            return;
        }
    } else {
        int choice = InputHandler::getChoice(1, currentPlayer.getHandsSize(), "Chose a card from hands to play: ");
        currentCard = &currentPlayer.getCard(choice - 1);
        currentPlayer.playCard(choice);
    }

    getInfo();

    int choice1 = InputHandler::getChoice(1, 2, "Whether to declare a region? (1 for yes, 2 for not)");
    if (choice1 == 1) {
        int regionChoice = InputHandler::getChoice(1, 9, "Choose a region to declare");
        regionsManager.getRegion(regionChoice).claim(currentPlayer);
    }

    getInfo();

    if (troopCardPile.isEmpty() && tacticsCardPile.isEmpty()) {
        std::cout << "Both card piles are empty." << std::endl;
    } else if (!troopCardPile.isEmpty() && tacticsCardPile.isEmpty()) {
        currentPlayer.drawCard(troopCardPile);
    } else if (troopCardPile.isEmpty() && !tacticsCardPile.isEmpty()) {
        currentPlayer.drawCard(tacticsCardPile);
    } else {
        int choice = InputHandler::getChoice(1, 2, "1. Draw from troop card pile 2. Draw from tactics card pile");
        if (choice == 1) {
            currentPlayer.drawCard(troopCardPile);
        } else {
            currentPlayer.drawCard(tacticsCardPile);
        }
    }

    getInfo();

    currentTurn++;
}

bool Game::isGameOver() {
    const Player& currentPlayer = getCurrentPlayer();
    int consecutiveRegions = 0;
    int totalRegions = 0;

    for (size_t i = 0; i < regionsManager.getRegionsCount(); i++) {
        const Player* owner = regionsManager.getRegion(i).getOwner();
        if (owner == &currentPlayer) {
            consecutiveRegions++;
            totalRegions++;

            if (consecutiveRegions == 3) {
                return true;
            }
        } else {
            consecutiveRegions = 0;  // Reset the consecutive count
        }
    }

    if (totalRegions >= 5) {
        return true;
    }

    return false;
}

