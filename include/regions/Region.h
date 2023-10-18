#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "Player.h"
#include "TacticsCard.h"


class Region {
private:
    size_t MaxTroopCard = 3;
    const Player* owner = nullptr;
    std::map<size_t , std::vector<const Card*>> player_cards;

public:
    const Player& getOwner() const;

    bool isClaimable(const Player&) const;

    bool isFull(const Player&) const;

    void claim(const Player& player);

    bool addCard(const Player&, const Card&);

    bool removeCard(const Player&, const Card&);

    void displayCardsOfPlayer() const;

    void displayOccupationInfo() const;
};