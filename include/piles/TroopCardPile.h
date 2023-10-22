#pragma once

#include "Pile.h"
#include "Deck.h"


class TroopCardPile : public Pile {
public:
    explicit TroopCardPile(const Deck&);
};
