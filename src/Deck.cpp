#include "Deck.h"


Deck::Deck() {
    for (Color color : EnumRange<Color>()) {
        for (Number number : EnumRange<Number>()) {
            auto tmp = new TroopCard(color, number);
            tmp->setEffect(new TroopCardEffectStrategy);
            troopCards.push_back(tmp);
        }
    }

    for (TacticsType tactics : EnumRange<TacticsType>()) {
        CardEffectStrategy* strategy = nullptr;
        switch (tactics) {
            case TacticsType::LEADER:
                strategy = new LeaderTacticsEffectStrategy;
                break;
            case TacticsType::COMPANION_CAVALRY:
                strategy = new CompanionCavalryEffectStrategy;
                break;
            case TacticsType::SHIELD_BEARERS:
                strategy = new ShieldBearersTacticsEffectStrategy;
                break;
            case TacticsType::FOG:
                strategy = new FogTacticsEffectStrategy;
                break;
            case TacticsType::MUD:
                strategy = new MudTacticsEffectStrategy;
                break;
            case TacticsType::SCOUT:
                strategy = new ScoutTacticsEffectStrategy;
                break;
            case TacticsType::REDEPLOY:
                strategy = new RedeployTacticsEffectStrategy;
                break;
            case TacticsType::DESERTER:
                strategy = new DeserterTacticsEffectStrategy;
                break;
            case TacticsType::TRAITOR:
                strategy = new TraitorTacticsEffectStrategy;
                break;
            default:
                break;
        }

        if (tactics == TacticsType::LEADER || tactics == TacticsType::COMPANION_CAVALRY || tactics == TacticsType::SHIELD_BEARERS) {
            if (tactics == TacticsType::LEADER) {
                auto card1 = new SpecialTacticsCard(TacticsType::LEADER);
                card1->setEffect(strategy);
                tacticsCards.push_back(card1);

                // Creating a second instance for the LEADER card
                auto card2 = new SpecialTacticsCard(TacticsType::LEADER);
                card2->setEffect(new LeaderTacticsEffectStrategy);
                tacticsCards.push_back(card2);
            } else {
                auto card = new SpecialTacticsCard(tactics);
                card->setEffect(strategy);
                tacticsCards.push_back(card);
            }
        } else {
            auto card = new TacticsCard(tactics);
            card->setEffect(strategy);
            tacticsCards.push_back(card);
        }
    }
}


Deck::~Deck() {
    for (auto& card : troopCards) {
        delete card;
    }
    for (auto& card : tacticsCards) {
        delete card;
    }
}

const Card& Deck::getTroopCard(size_t i) const {
    if (i >= troopCards.size()) {
        throw std::out_of_range("Requested index is out of bounds for troop cards.");
    }

    return *troopCards[i];
}

const Card& Deck::getTacticsCard(size_t i) const {
    if (i >= tacticsCards.size()) {
        throw std::out_of_range("Requested index is out of bounds for tactics cards.");
    }

    return *tacticsCards[i];
}

size_t Deck::getTroopCardNb() const { return troopCards.size(); }
size_t Deck::getTacticsCardNb() const { return tacticsCards.size(); }
