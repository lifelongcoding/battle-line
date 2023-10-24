#pragma once

#include <map>
#include <string>

#include "Card.h"
#include "TroopCard.h"


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

class SpecialTacticsCard : public TacticsCard {
private:
    Color color = Color::NONE;
    Number number = Number::NONE;
public:
    inline explicit SpecialTacticsCard(TacticsType t) : TacticsCard(t) {}

    void setColor(Color c) { color = c; }
    void setNumber(Number n) { number = n; }
    void setTypeToTroop() { cardType = CardType::TROOP_CARD; }

    Color getColor() const { return color; }
    Number getNumber() const { return number; }

    void getInfo() const override;
};
