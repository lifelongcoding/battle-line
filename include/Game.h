#pragma once

#include "Player.h"
#include "RegionsManager.h"
#include "Deck.h"
#include "TroopCardPile.h"
#include "TacticsCardPile.h"
#include "DiscardPile.h"
#include "InputHandler.h"

enum class TurnState {
    START_TURN,
    CHECK_INITIAL_CONDITIONS,
    PLAY_CARD,
    DECLARE_REGION,
    CHOOSE_REGION,
    DRAW_CARD,
    SKIP_TURN,
    END_TURN
};

class Game {
private:
    static Game* instance;

    std::vector<Player> players;
    RegionsManager regionsManager;
    Deck deck;
    TroopCardPile troopCardPile;
    TacticsCardPile tacticsCardPile;
    DiscardPile discardPile;

    const Card* currentCard = nullptr;
    int currentPlayerIndex = -1;
    int currentTurn = 1;
    int gameVersion = -1; // 0 for standard, 1 for tactical

    Game() : regionsManager(9), deck(), troopCardPile(deck), tacticsCardPile(deck) {}

public:
    static Game* getInstance() {
        if (!instance) {
            instance = new Game();
        }
        return instance;
    }

    ~Game() = default;
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Player& getCurrentPlayer() { return players[currentPlayerIndex]; }
    Player& getAnotherPlayer() { return players[(currentPlayerIndex + 1) % players.size()]; }
    const Card& getCurrentCard() { return *currentCard; }
    RegionsManager& getRegionsManager() { return regionsManager; }
    TroopCardPile& getTroopCardPile() { return troopCardPile; }
    TacticsCardPile& getTacticsCardPile() { return tacticsCardPile; }
    DiscardPile& getDiscardPile() { return discardPile; }

    int getCurrentTurn() const { return currentTurn; }

    void init();

    void playTurn();

    void nextTurn() { currentPlayerIndex = (currentPlayerIndex + 1) % players.size(); }

    bool isGameOver();

    void getInfo() {
        std::cout << "current turn: " << getCurrentTurn() << '\t' << "current player: "
            << players[currentPlayerIndex].getName() << std::endl;

        std::cout << players[currentPlayerIndex].getName() << ": ";
        players[currentPlayerIndex].getHandsInfo();
        std::cout << std::endl;

        regionsManager.displayRegionsInfo();
    }
};
