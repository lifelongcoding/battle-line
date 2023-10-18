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