#include "TacticsCard.h"
#include <iostream>

void TacticsCard::getInfo() const {
    std::cout << "[" << TacticsNames.at(this->getTacticsType()) << "]";
}

void SpecialTacticsCard::getInfo() const {
    if (cardType == CardType::TACTICS_CARD) {
        std::cout << "[" << TacticsNames.at(this->getTacticsType()) << "]";
    } else {
        std::cout << "[" << ColorNames.at(color) << ", " << static_cast<int>(number)+1 << "]";
    }
}