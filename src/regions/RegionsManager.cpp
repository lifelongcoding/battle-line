#include "RegionsManager.h"


bool RegionsManager::canPlaceTroopCard(const Player& player) const {
    return std::any_of(regions.begin(), regions.end(), [&player](const auto& region) {
        return !region->isFull(player);
    });
}


void RegionsManager::displayRegionsInfo() const {
    for (size_t i = 0; i < regions.size(); i++) {
        Region* region = regions[i];
        std::cout << "region: " << i << std::endl;
        region->displayOccupationInfo();
        std::cout << std::endl;
        region->displayCardsOfPlayer();
        std::cout << std::endl;
    }
}