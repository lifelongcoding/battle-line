#include "DiscardPile.h"

#include <iostream>


void DiscardPile::getInfo() const {
    for (size_t i = 0; i < remainingCards(); i++) {
        cards[i]->getInfo();
        std::cout << ", ";
    }
}