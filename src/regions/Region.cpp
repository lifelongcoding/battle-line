#include "Region.h"

const Player& Region::getOwner() const {
    return *owner;
}

void Region::claim(const Player& player) {
    owner = &player;
}

bool Region::isClaimable(const Player&) const {

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

bool Region::removeCard(const Player& player, const Card& cardToRemove) {
    size_t playerId = player.getId();

    if (player_cards.find(playerId) == player_cards.end()) {
        return false;
    }

    auto& playerCardList = player_cards[playerId];
    auto it = std::remove(playerCardList.begin(), playerCardList.end(), &cardToRemove);

    if (it != playerCardList.end()) {
        playerCardList.erase(it, playerCardList.end());
        return true;
    }

    return false;
}

void Region::displayCardsOfPlayer() const {
    for (auto& pair : player_cards) {
        auto &cards = pair.second;
        for (auto &card: cards) {
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
