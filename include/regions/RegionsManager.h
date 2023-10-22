#pragma once

#include <iostream>
#include <vector>

#include "Region.h"


class RegionsManager {
private:
    std::vector<Region*> regions;
public:
    explicit RegionsManager(size_t num) {
        regions.reserve(num);
        for (size_t i = 0; i < num; i++) {
            regions.push_back(new Region());
        }
    }

    ~RegionsManager() {
        for (auto& region : regions) {
            delete region;
        }
    }

    Region& getRegion(size_t index) const {
        return *regions[index];
    }

    bool canPlaceTroopCard(const Player&) const;

    void displayRegionsInfo() const;
};
