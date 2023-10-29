#include "RegionsManager.h"


bool RegionsManager::canPlaceTroopCard(const Player& player) const {
    return std::any_of(regions.begin(), regions.end(), [&player](const auto& region) {
        return !region->isFull(player);
    });
}


void RegionsManager::displayRegionsInfo() const {
    for (size_t i = 0; i < regions.size(); i++) {
        Region* region = regions[i];
        std::cout << "region: " << i << "\t";
    }
    std::cout << std::endl;

    for (auto& region : regions) {
        region->displayOccupationInfo();
        std::cout << "\t";
    }
    std::cout << std::endl;

    for (auto& region : regions) {
        region->displayCardsOfPlayer();
        std::cout << "\t";
    }
    std::cout << std::endl;
}