#include "TacticsCard.h"
#include <iostream>

void TacticsCard::getInfo() const {
    std::cout << "[" << TacticsNames.at(this->getTacticsType()) << "]";
}