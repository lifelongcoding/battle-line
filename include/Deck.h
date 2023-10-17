#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>

#include "TroopCard.h"
#include "TacticsCard.h"


template<typename T>
class EnumRange {
public:
    class Iterator {
        using Underlying = typename std::underlying_type<T>::type;

    public:
        explicit Iterator(Underlying value) : value(value) {}
        T operator*() const { return static_cast<T>(value); }
        Iterator& operator++() { ++value; return *this; }
        bool operator!=(const Iterator& other) const { return value != other.value; }

    private:
        Underlying value;
    };

    Iterator begin() const { return Iterator(static_cast<typename std::underlying_type<T>::type>(0)); }
    Iterator end() const { return Iterator(static_cast<typename std::underlying_type<T>::type>(T::ENUM_SIZE)); }
};

class Deck {
private:
    std::vector<const TroopCard*> troopCards;
    std::vector<const TacticsCard*> tacticsCards;

public:
    Deck();
    ~Deck();

    const Card& getTroopCard(size_t i) const;
    const Card& getTacticsCard(size_t i) const;

    size_t getTroopCardNb() const;
    size_t getTacticsCardNb() const;
};
