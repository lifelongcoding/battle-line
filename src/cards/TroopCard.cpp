#include "TroopCard.h"
#include <iostream>


void TroopCard::getInfo() const {
    std::cout << "[" << ColorNames.at(this->getColor()) << ", " << static_cast<int>(this->getNumber())+1 << "]";
}

