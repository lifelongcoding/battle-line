#include "TroopCardPile.h"


TroopCardPile::TroopCardPile(const Deck& deck) {
    for (size_t i = 0; i < deck.getTroopCardNb(); i++) {
        addCard(deck.getTroopCard(i));
    }
}
