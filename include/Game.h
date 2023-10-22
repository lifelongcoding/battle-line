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
    Card* currentCard = nullptr;

    Game() : regionsManager(9), deck(), troopCardPile(deck), tacticsCardPile(deck) {
        players.emplace_back(0, "Alice");
        players.emplace_back(1, "Tommy");
        troopCardPile.shuffle();
        tacticsCardPile.shuffle();
        currentPlayerIndex = 0;
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

    Card& getCurrentCard() { return *currentCard; }

    RegionsManager& getRegionsManager() { return regionsManager; }

    TroopCardPile& getTroopCardPile() { return troopCardPile; }

    TacticsCardPile& getTacticsCardPile() { return tacticsCardPile; }

    DiscardPile& getDiscardPile() { return discardPile; }

    void playTurn();

    void nextTurn() {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }
};

Game* Game::instance = nullptr;
