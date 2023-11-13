#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "tuple"
#include <algorithm>

#include "Player.h"
#include "Card.h"
#include "TroopCard.h"
#include "TacticsCard.h"

using cardtype = std::tuple<Color, Number>;

enum class FormationStrength { HOST, SKIRMISH, BATTALION, PHALANX, WEDGE };

class Region {
private:
    size_t MaxTroopCard = 3;
    const Player* owner = nullptr;
    std::map<size_t, std::vector<const Card*>> player_cards;
    const Player* lastOperator = nullptr;

public:
    const Player* getOwner() const;

    bool isClaimable(const Player&) const;

    bool isFull(const Player&) const;

    void claim(const Player& player);

    void addCard(const Player&, const Card&);

    void removeCard(const Card&);

    void setMaxTroopCard(size_t);

    void displayCardsOfPlayer() const;

    void displayOccupationInfo() const;

    static std::tuple<Color, Number> createTroopCardTuple(const TroopCard* card) ;

    std::vector<std::tuple<Color, Number>> createRegionTuple(size_t id) const;

    std::pair<FormationStrength, int> getFormationStrength(std::vector<cardtype>) const;

    static std::vector<std::vector<std::tuple<Color, Number>>> predictFormationStrength(const std::vector<cardtype>&, const std::vector<const TroopCard*>&) ;

    const Card& getCard(size_t playerId, size_t index) const {
        return *player_cards.at(playerId)[index];
    }

    size_t getSize(size_t id) {
        return player_cards.at(id).size();
    }
};
