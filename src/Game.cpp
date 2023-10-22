#include "Game.h"


void Game::playTurn() {
    Player& currentPlayer = getCurrentPlayer();

    if (!currentPlayer.hasTroopCard() || !regionsManager.canPlaceTroopCard(currentPlayer)) {
        if (currentPlayer.hasTacticsCard()) {
            int choice = InputHandler::getChoice(1, 2, "1. Play a tactics card 2. Skip");
            if (choice == 1) {
                int cardChoice = InputHandler::getChoice(1, currentPlayer.getHandsSize(), "Chose a card from hands to play: ");
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
        currentPlayer.playCard(choice);
    }

    int choice1 = InputHandler::getChoice(1, 2, "Whether declare a region? (1 for yes, 2 for not)");
    if (choice1 == 1) {
        int regionChoice = InputHandler::getChoice(1, 9, "Choose a region to declare");
        regionsManager.getRegion(regionChoice).claim(currentPlayer);
    }

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
}
