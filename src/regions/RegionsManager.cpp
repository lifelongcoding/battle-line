#include "RegionsManager.h"


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