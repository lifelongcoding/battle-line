#pragma once

#include "Card.h"
#include <map>
#include <string>


enum class TacticsType { LEADER, COMPANION_CAVALRY, SHIELD_BEARERS, FOG, MUD, SCOUT, REDEPLOY, DESERTER, TRAITOR, ENUM_SIZE };

const std::map<TacticsType, std::string> TacticsNames = {
        { TacticsType::LEADER, "LEADER" },
        { TacticsType::COMPANION_CAVALRY, "COMPANION_CAVALRY" },
        { TacticsType::SHIELD_BEARERS, "SHIELD_BEARERS" },
        { TacticsType::FOG, "FOG" },
        { TacticsType::MUD, "MUD" },
        { TacticsType::SCOUT, "SCOUT" },
        { TacticsType::REDEPLOY, "REDEPLOY" },
        { TacticsType::DESERTER, "DESERTER" },
        { TacticsType::TRAITOR, "TRAITOR" }
};

class TacticsCard : public Card {
private:
    TacticsType tacticsType;
public:
    inline explicit TacticsCard(TacticsType t) : Card(CardType::TACTICS_CARD), tacticsType(t) {}

    inline TacticsType getTacticsType() const { return tacticsType; }

    void getInfo() const override;
};
