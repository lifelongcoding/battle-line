#pragma once

#include "Pile.h"
#include "Deck.h"


class TacticsCardPile : public Pile {
public:
    explicit TacticsCardPile(const Deck&);
};
