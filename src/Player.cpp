#include "Player.h"

size_t Player::getId() const {
    return id;
}

std::string Player::getName() const {
    return name;
}

void Player::drawCard(Pile& pile) {
    hands.push_back(&pile.drawCard());
}

void Player::playCard(size_t index) {

}

bool Player::hasTroopCard() {
    return std::any_of(hands.begin(), hands.end(), [](const Card* card) {
        return card->getType() == CardType::TROOP_CARD;
    });
}

bool  Player::hasTacticsCard() {
    return std::any_of(hands.begin(), hands.end(), [](const Card* card) {
        return card->getType() == CardType::TACTICS_CARD;
    });
}
