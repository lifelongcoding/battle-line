#include "Game.h"


Game* Game::instance = nullptr;

void Game::init() {
    std::string playerName1, playerName2;
    int isPlayer1Ai = 0, isPlayer2Ai = 0;
    playerName1 = InputHandler::getStringChoice("Enter name for Player 1: ");
    playerName2 = InputHandler::getStringChoice("Enter name for Player 2: ");

    std::cout << "Is player1 a bot? (0 for not, 1 for yes)";
    std::cin >> isPlayer1Ai;
    std::cout << "Is player2 a bot? (0 for not, 1 for yes)";
    std::cin >> isPlayer2Ai;

    players.emplace_back(0, playerName1);
    players.emplace_back(1, playerName2);

    if (isPlayer1Ai) {
        players[0].setPlayerType(PlayerType::AI_PLAYER);
    }
    if (isPlayer2Ai) {
        players[1].setPlayerType(PlayerType::AI_PLAYER);
    }

    std::cout << "Choose game version (0 for Standard, 1 for Tactical): ";
    std::cin >> gameVersion;
    std::cin.ignore(); // To handle the newline character

    troopCardPile.shuffle();
    tacticsCardPile.shuffle();

    for (int i = 0; i < 7; i++) {
        players[0].drawCard(troopCardPile);
        players[1].drawCard(troopCardPile);
    }

    currentPlayerIndex = 0;
}

void Game::playTurn() {
    TurnState currentState = TurnState::START_TURN;
    Player& currentPlayer = getCurrentPlayer();
    bool isAi = (currentPlayer.getPlayerType() == PlayerType::AI_PLAYER);

    while(currentState != TurnState::END_TURN) {
        switch (currentState) {
            case TurnState::START_TURN: {
                currentState = TurnState::CHECK_INITIAL_CONDITIONS;
                break;
            }

            case TurnState::CHECK_INITIAL_CONDITIONS: {
                if (!currentPlayer.hasTroopCard() || !regionsManager.canPlaceTroopCard(currentPlayer)) {
                    currentState = currentPlayer.hasTacticsCard() ? TurnState::PLAY_CARD : TurnState::DECLARE_REGION;
                } else {
                    currentState = TurnState::PLAY_CARD;
                }
                break;
            }

            case TurnState::PLAY_CARD: {
                int choice;
                if (isAi) {
                    choice = generateRandomNumber(1, currentPlayer.getHandsSize());
                } else choice = InputHandler::getChoice(1, currentPlayer.getHandsSize(), "Choose a card from hands to play: ");
                currentCard = &currentPlayer.getCard(choice - 1);
                currentPlayer.playCard(choice);
                currentState = TurnState::DECLARE_REGION;
                break;
            }

            case TurnState::DECLARE_REGION: {
                getInfo();
                int choice1;
                if (isAi) {
                    choice1 = 1;
                } else {
                    choice1 = InputHandler::getChoice(1, 2, "Whether to declare a region? (1 for yes, 2 for not)");
                }

                if (choice1 == 1) {
                    currentState = TurnState::CHOOSE_REGION;
                } else {
                    currentState = TurnState::DRAW_CARD;
                }
                break;
            }

            case TurnState::CHOOSE_REGION: {
                int regionChoice;
                if (isAi) {
                    regionChoice = generateRandomNumber(1, 9);
                } else {
                    regionChoice = InputHandler::getChoice(1, 9, "Choose a region to declare");
                }
                regionsManager.getRegion(regionChoice - 1).claim(currentPlayer);
                currentState = TurnState::DRAW_CARD;
                break;
            }


            case TurnState::DRAW_CARD: {
                if (gameVersion == 0) {
                    if (troopCardPile.isEmpty()) {
                        std::cout << "Troop card pile is empty." << std::endl;
                        getInfo();
                    } else {
                        currentPlayer.drawCard(troopCardPile);
                        getInfo();
                    }
                } else {
                    if (troopCardPile.isEmpty() && tacticsCardPile.isEmpty()) {
                        std::cout << "Both card piles are empty." << std::endl;
                    } else if (!troopCardPile.isEmpty() && tacticsCardPile.isEmpty()) {
                        currentPlayer.drawCard(troopCardPile);
                    } else if (troopCardPile.isEmpty() && !tacticsCardPile.isEmpty()) {
                        currentPlayer.drawCard(tacticsCardPile);
                    } else {
                        int cardPileChoice = InputHandler::getChoice(1, 2, "1. Draw from troop card pile 2. Draw from tactics card pile");
                        if (cardPileChoice == 1) {
                            currentPlayer.drawCard(troopCardPile);
                            getInfo();
                        } else {
                            currentPlayer.drawCard(tacticsCardPile);
                            getInfo();
                        }
                    }
                }
                currentState = TurnState::END_TURN;
                break;
            }
        }
    }

    currentTurn++;
    currentState = TurnState::START_TURN;
}

void Game::nextTurn() {
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
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

int Game::generateRandomNumber(int min, int max) {
    if (min > max) {
        return -1;
    }
    std::uniform_int_distribution<int> uni(min, max);
    return uni(rng);
}

void Game::getInfo() {
    std::cout << "current turn: " << getCurrentTurn() << '\t' << "current player: "
              << players[currentPlayerIndex].getName() << std::endl;

    std::cout << players[currentPlayerIndex].getName() << ": ";
    players[currentPlayerIndex].getHandsInfo();
    std::cout << std::endl;

    regionsManager.displayRegionsInfo();
}
