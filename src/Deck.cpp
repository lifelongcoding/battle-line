#include "Deck.h"


Deck::Deck() {
    for (Color color : EnumRange<Color>()) {
        for (Number number : EnumRange<Number>()) {
            troopCards.push_back(new TroopCard(color, number));
        }
    }

    for (TacticsType tactics : EnumRange<TacticsType>()) {
        if (tactics == TacticsType::LEADER) {
            tacticsCards.push_back(new TacticsCard(TacticsType::LEADER));
            tacticsCards.push_back(new TacticsCard(TacticsType::LEADER));
        } else {
            tacticsCards.push_back(new TacticsCard(tactics));
        }
    }
}

Deck::~Deck() {
    for (const Card* card : troopCards) {
        delete card;
    }
    for (const Card* card : tacticsCards) {
        delete card;
    }
}

const Card& Deck::getTroopCard(size_t i) const {
    if (i >= troopCards.size()) {
        throw std::out_of_range("Requested index is out of bounds for troop cards.");
    }

    return *troopCards[i];
}

const Card& Deck::getTacticsCard(size_t i) const {
    if (i >= tacticsCards.size()) {
        throw std::out_of_range("Requested index is out of bounds for tactics cards.");
    }

    return *tacticsCards[i];
}

size_t Deck::getTroopCardNb() const { return troopCards.size(); }
size_t Deck::getTacticsCardNb() const { return tacticsCards.size(); }
