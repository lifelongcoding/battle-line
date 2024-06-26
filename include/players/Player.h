#pragma once

#include <string>
#include <vector>

#include "Card.h"
#include "Pile.h"

enum class PlayerType {
    HUMAN_PLAYER,
    AI_PLAYER,
};

class Player {
private:
    size_t id;
    std::string name;
    std::vector<const Card*> hands;
    PlayerType playerType = PlayerType::HUMAN_PLAYER;
public:
    Player(size_t i, std::string n) : id(i), name(std::move(n)) {}

    std::string getName() const;
    size_t getId() const;
    void getHandsInfo() const;

    void drawCard(Pile&);
    void playCard(size_t index);
    void removeCard(size_t index) {
        if (index < hands.size()) {
            hands.erase(hands.begin() + static_cast<std::vector<const Card*>::difference_type>(index));
        }
    }

    const Card& getCard(size_t index) const { return *hands[index]; }
    const Card& getCard(size_t index) { return *hands[index]; }

    size_t getHandsSize() const { return hands.size(); }

    bool hasTroopCard();
    bool hasTacticsCard();

    void setPlayerType(PlayerType t) { playerType = t; }
    PlayerType getPlayerType() const { return playerType; }
};
