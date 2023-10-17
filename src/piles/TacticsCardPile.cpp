#include "TacticsCardPile.h"


TacticsCardPile::TacticsCardPile(const Deck& deck) {
    for (size_t i = 0; i < deck.getTacticsCardNb(); i++) {
        addCard(deck.getTacticsCard(i));
    }
}
