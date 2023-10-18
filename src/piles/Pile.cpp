#include "Pile.h"


void Pile::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

const Card& Pile::drawCard() {
    if (!cards.empty()) {
        const Card* lastCard = cards.back();
        cards.pop_back();
        return *lastCard;
    }

    throw std::runtime_error("Attempted to draw from an empty pile.");
}
