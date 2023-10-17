#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>

#include "Card.h"


class Pile {
protected:
    std::vector<const Card*> cards;
public:
    void shuffle();

    const Card& drawCard();

    inline void addCard(const Card& cardToAdd) { cards.push_back(&cardToAdd); }

    inline bool isEmpty() const { return cards.empty(); }

    inline size_t remainingCards() const { return cards.size(); }
};
