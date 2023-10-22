#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "Player.h"
#include "TacticsCard.h"


enum class FormationStrength { HOST, SKIRMISH, BATTALION, PHALANX, WEDGE };

class Region {
private:
    size_t MaxTroopCard = 3;
    const Player* owner = nullptr;
    std::map<size_t, std::vector<const Card*>> player_cards;

public:
    const Player& getOwner() const;

    bool isClaimable(const Player&) const;

    bool isFull(const Player&) const;

    void claim(const Player& player);

    bool addCard(const Player&, const Card&);

    void removeCard(const Card&);

    void setMaxTroopCard(size_t);

    void displayCardsOfPlayer() const;

    void displayOccupationInfo() const;

    FormationStrength getFormationStrength(size_t) const;

    const Card& getCard(size_t playerId, size_t index) const {
        return *player_cards.at(playerId)[index];
    }
};
