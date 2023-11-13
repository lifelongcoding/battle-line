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
    std::vector<const TroopCard*> known_cards;

    size_t playerId = player.getId();
    auto currentPlayerCards = createRegionTuple(playerId);
    auto currentPlayerFormation = getFormationStrength(currentPlayerCards);
    std::vector<cardtype> otherPlayerCards;
    for (auto& pair : player_cards) {
        if (pair.first != playerId) {
            otherPlayerCards = createRegionTuple(pair.first);
        }
    }
    if (otherPlayerCards.size() == MaxTroopCard) {
        auto otherPlayerFormation = getFormationStrength(otherPlayerCards);
        if (otherPlayerFormation.first > currentPlayerFormation.first || otherPlayerFormation.first == currentPlayerFormation.first && otherPlayerFormation.second > currentPlayerFormation.second) {
            return false;
        }
    } else {
        auto possibleFormation = predictFormationStrength(otherPlayerCards, known_cards);
        for (auto& com : possibleFormation) {
            auto st = getFormationStrength(com);
            if (st.first > currentPlayerFormation.first || st.first == currentPlayerFormation.first && st.second > currentPlayerFormation.second) {
                return false;
            }
        }
    }

    return true;
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

void Region::addCard(const Player& player, const Card& card) {
    size_t playerId = player.getId();

    if (player_cards.find(playerId) == player_cards.end()) {
        player_cards[playerId] = std::vector<const Card*>();
    }

    player_cards[playerId].push_back(&card);
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
            std::cout << " ";
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

std::pair<FormationStrength, int> Region::getFormationStrength(std::vector<cardtype> troopCards) const {
    if (troopCards.size() != MaxTroopCard) {
        throw std::runtime_error("Invalid number of cards.");
    }

    bool sameColor = std::all_of(troopCards.begin() + 1, troopCards.end(),
                                 [&troopCards](const cardtype& card) {
                                     return std::get<0>(card) == std::get<0>(troopCards[0]);
                                 });

    std::vector<int> numbers;
    std::transform(troopCards.begin(), troopCards.end(), std::back_inserter(numbers),
                   [](const cardtype& card) { return static_cast<int>(std::get<1>(card)); });
    std::sort(numbers.begin(), numbers.end());
    bool consecutiveNumbers = std::adjacent_find(numbers.begin(), numbers.end(),
                                                 [](int a, int b) { return b - a != 1; }) == numbers.end();

    bool allSameNumber = std::all_of(troopCards.begin() + 1, troopCards.end(),
                                     [&troopCards](const cardtype& card) { return std::get<1>(card) == std::get<1>(troopCards[0]); });

    int sumNumbers = std::accumulate(numbers.begin(), numbers.end(), 0);

    if (sameColor && consecutiveNumbers) {
        return {FormationStrength::WEDGE, sumNumbers};
    }

    if (allSameNumber) {
        return {FormationStrength::PHALANX, sumNumbers};
    }

    if (sameColor) {
        return {FormationStrength::BATTALION, sumNumbers};
    }

    if (consecutiveNumbers) {
        return {FormationStrength::SKIRMISH, sumNumbers};
    }

    return {FormationStrength::HOST, sumNumbers};
}

std::tuple<Color, Number> Region::createTroopCardTuple(const TroopCard* card) {
    return std::make_tuple(card->getColor(), card->getNumber());
}

std::vector<std::tuple<Color, Number>> Region::createRegionTuple(size_t id) const {
    std::cout << id;
    for (auto& pair : player_cards) {
        std::cout << pair.first;
    }
    const std::vector<const Card*>& cards = player_cards.at(id);
    std::vector<const TroopCard*> troopCards;
    for (const Card* card : cards) {
        if (card->getType() == CardType::TROOP_CARD) {
            troopCards.push_back(dynamic_cast<const TroopCard*>(card));
        }
    }

    std::vector<std::tuple<Color, Number>> vector;
    for (auto& card : troopCards) {
        vector.push_back(createTroopCardTuple(card));
    }

    return vector;
}

std::vector<std::vector<std::tuple<Color, Number>>>
Region::predictFormationStrength(const std::vector<cardtype> &opponent_cards,
                                 const std::vector<const TroopCard *> &known_cards) {
    std::vector<std::tuple<Color, Number>> available_cards_tuple;
    std::vector<std::tuple<Color, Number>> known_cards_tuple;
    for (auto& known_card : known_cards) {
        known_cards_tuple.push_back(createTroopCardTuple(known_card));
    }

    for (int i = 0; i < static_cast<int>(Color::ENUM_SIZE); ++i) {
        for (int j = 0; j < static_cast<int>(Number::ENUM_SIZE); ++j) {
            auto color = static_cast<Color>(i);
            auto number = static_cast<Number>(j);
            auto card = std::make_tuple(color, number);

            // Check if the card is not in the known_cards
            auto it = std::find_if(known_cards_tuple.begin(), known_cards_tuple.end(),
                                   [&](const std::tuple<Color, Number> &known_card) {
                                       return std::get<0>(known_card) == std::get<0>(card) &&
                                              std::get<1>(known_card) == std::get<1>(card);
            });

            if (it == known_cards_tuple.end()) {
                available_cards_tuple.push_back(card);
            }
        }
    }
    std::vector<std::vector<cardtype>> possible_combination;

    std::vector<bool> v(available_cards_tuple.size());
    std::fill(v.begin(), v.begin() + (3 - opponent_cards.size()), true);

    do {
        std::vector<std::tuple<Color, Number>> potential_hand = opponent_cards;
        for (int i = 0; i < available_cards_tuple.size(); ++i) {
            if (v[i]) {
                potential_hand.push_back(available_cards_tuple[i]);
            }
        }
        possible_combination.push_back(potential_hand);
    } while (std::prev_permutation(v.begin(), v.end()));

    return possible_combination;
}
