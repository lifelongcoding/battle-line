#pragma once

#include "Card.h"


enum class TacticsType { LEADER, COMPANION_CAVALRY, SHIELD_BEARERS, FOG, MUD, SCOUT, REDEPLOY, DESERTER, TRAITOR, ENUM_SIZE };

class TacticsCard : public Card {
private:
    TacticsType tacticsType;
public:
    inline explicit TacticsCard(TacticsType t) : Card(CardType::TACTICS_CARD), tacticsType(t) {}

    inline TacticsType getTacticsType() const { return tacticsType; }
};
