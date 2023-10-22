#pragma once

#include <string>
#include <vector>

#include "Card.h"
#include "Pile.h"


class Player {
private:
    size_t id;
    std::string name;
    std::vector<const Card*> hands;
public:
    Player(size_t i, std::string n) : id(i), name(std::move(n)) {}

    std::string getName() const;
    size_t getId() const;

    void drawCard(Pile&);
    void playCard(size_t index);
    void removeCard(size_t index) {
        if (index < hands.size()) {
            hands.erase(hands.begin() + static_cast<std::vector<const Card*>::difference_type>(index));
        }
    }

    const Card& getCard(size_t index) const { return *hands[index]; }

    size_t getHandsSize() const { return hands.size(); }

    bool hasTroopCard();
    bool hasTacticsCard();
};
