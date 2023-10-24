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
    hands[index - 1]->executeEffect();
    removeCard(index - 1);
}

bool Player::hasTroopCard() {
    return std::any_of(hands.begin(), hands.end(), [](auto& card) {
        return card->getType() == CardType::TROOP_CARD;
    });
}

bool Player::hasTacticsCard() {
    return std::any_of(hands.begin(), hands.end(), [](auto& card) {
        return card->getType() == CardType::TACTICS_CARD;
    });
}

void Player::getHandsInfo() const {
    for (auto& card : hands) {
        card->getInfo();
    }
}
