#include "Region.h"

const Player* Region::getOwner() const {
    return owner;
}

void Region::claim(const Player& player) {
    if (isClaimable(player)) {
        owner = &player;
    }
}

bool Region::isClaimable(const Player& player) const {
    size_t playerId = player.getId();
    FormationStrength currentPlayerFormation = getFormationStrength(playerId);
    FormationStrength otherPlayerFormation;
    for (auto& pair : player_cards) {
        if (pair.first != playerId) {
            otherPlayerFormation = getFormationStrength(pair.first);
        }
    }

    return (static_cast<int>(currentPlayerFormation) > static_cast<int>(otherPlayerFormation));
}

bool Region::isFull(const Player& player) const {
    size_t playerId = player.getId();
    if (player_cards.find(playerId) == player_cards.end()) {
        return false;
    }

    int troopCardCount = 0;
    for (const auto& card : player_cards.at(playerId)) {
        if (card->getType() == CardType::TROOP_CARD) {
            troopCardCount++;
        }
    }

    return troopCardCount >= MaxTroopCard;
}

bool Region::addCard(const Player& player, const Card& card) {
    size_t playerId = player.getId();

    if (player_cards.find(playerId) == player_cards.end()) {
        player_cards[playerId] = std::vector<const Card*>();
    }

    if (card.getType() == CardType::TROOP_CARD) {
        if (isFull(player)) {
            return false;
        }
    }

    player_cards[playerId].push_back(&card);
    return true;
}

void Region::removeCard(const Card& cardToRemove) {
    for (auto& pair : player_cards) {
        auto& cards = pair.second;
        auto it = std::find_if(cards.begin(), cards.end(),
                [&](const Card* card) { return card == &cardToRemove; });
        if (it != cards.end()) {
            cards.erase(it);
            return;
        }
    }
}

void Region::setMaxTroopCard(size_t num) {
    MaxTroopCard = num;
}

void Region::displayCardsOfPlayer() const {
    for (auto& pair : player_cards) {
        auto& cards = pair.second;
        for (auto& card: cards) {
            card->getInfo();
            std::cout << ", ";
        }
        std::cout << std::endl;
    }
}

void Region::displayOccupationInfo() const {
    if (owner == nullptr) {
        std::cout << "unoccupied";
    } else {
        std::cout << owner->getName();
    }
}

FormationStrength Region::getFormationStrength(size_t id) const {
    const std::vector<const Card*>& cards = player_cards.at(id);

    std::vector<const TroopCard*> troopCards;
    for (const Card* card : cards) {
        if (card->getType() == CardType::TROOP_CARD) {
            troopCards.push_back(dynamic_cast<const TroopCard*>(card));
        }
    }

    if (troopCards.size() != MaxTroopCard) {
        throw std::runtime_error("Invalid number of cards.");
    }

    bool sameColor = std::all_of(troopCards.begin() + 1, troopCards.end(),
                                 [&troopCards](const TroopCard* card) {
                                     return card->getColor() == troopCards[0]->getColor();
                                 });

    std::vector<int> numbers;
    std::transform(troopCards.begin(), troopCards.end(), std::back_inserter(numbers),
                   [](const TroopCard* card) { return static_cast<int>(card->getNumber()); });
    std::sort(numbers.begin(), numbers.end());
    bool consecutiveNumbers = std::adjacent_find(numbers.begin(), numbers.end(),
                                                 [](int a, int b) { return b - a != 1; }) == numbers.end();

    bool allSameNumber = std::all_of(troopCards.begin() + 1, troopCards.end(),
                                     [&troopCards](const TroopCard* card) { return card->getNumber() == troopCards[0]->getNumber(); });


    if (sameColor && consecutiveNumbers) {
        return FormationStrength::WEDGE;
    }

    if (allSameNumber) {
        return FormationStrength::PHALANX;
    }

    if (sameColor) {
        return FormationStrength::BATTALION;
    }

    if (consecutiveNumbers) {
        return FormationStrength::SKIRMISH;
    }

    return FormationStrength::HOST;
}
