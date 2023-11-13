#pragma once

#include "CardEffectStrategy.h"

enum class CardType { TROOP_CARD, TACTICS_CARD };

class Card {
protected:
    CardType cardType;
    const CardEffectStrategy* effectStrategy = nullptr;

public:
    inline explicit Card(CardType t) : cardType(t) {}

    inline CardType getType() const { return cardType; }

    virtual void getInfo() const = 0;

    void setEffect(const CardEffectStrategy* cardEffectStrategy) {
        effectStrategy = cardEffectStrategy;
    }
    void executeEffect() const {
        if (effectStrategy) {
            effectStrategy->executeEffect();
        }
    }
};
