#pragma once

#include "Player.h"
#include "RegionsManager.h"
#include "Deck.h"
#include "TroopCardPile.h"
#include "TacticsCardPile.h"
#include "DiscardPile.h"
#include "InputHandler.h"


class Game {
private:
    static Game* instance;

    std::vector<Player> players;
    RegionsManager regionsManager;
    Deck deck;
    TroopCardPile troopCardPile;
    TacticsCardPile tacticsCardPile;
    DiscardPile discardPile;

    int currentPlayerIndex;
    const Card* currentCard = nullptr;
    int currentTurn = 1;

    Game() : regionsManager(9), deck(), troopCardPile(deck), tacticsCardPile(deck) {
        players.emplace_back(0, "Alice");
        players.emplace_back(1, "Tommy");
        troopCardPile.shuffle();
        tacticsCardPile.shuffle();
        currentPlayerIndex = 0;

        for (int i = 0; i < 7; i ++) {
            players[0].drawCard(troopCardPile);
            players[1].drawCard(troopCardPile);
        }
    }

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

    int getCurrentTurn() { return currentTurn; }


    void playTurn();

    void nextTurn() {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }

    bool isGameOver();

    void getInfo() {
        std::cout << "current turn: " << currentTurn << '\t' << "current player: "
            << players[currentPlayerIndex].getName() << std::endl;

        std::cout << players[currentPlayerIndex].getName() << ": ";
        players[currentPlayerIndex].getHandsInfo();
        std::cout << std::endl;

        regionsManager.displayRegionsInfo();
    }
};
