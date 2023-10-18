#pragma once

#include <string>
#include <vector>

#include "Card.h"
#include "Pile.h"


struct CardArgs {

};


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
};
