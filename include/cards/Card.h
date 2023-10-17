#pragma once


enum class CardType { TROOP_CARD, TACTICS_CARD };

class Card {
protected:
    CardType cardType;

public:
    inline explicit Card(CardType t) : cardType(t) {}

    inline CardType getType() const { return cardType; }

    virtual void getInfo() const {}
};
