#pragma once

#include "Card.h"


enum class Color { RED, BLUE, GREEN, YELLOW, GRAY, PURPLE, ENUM_SIZE };
enum class Number { ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, ENUM_SIZE };

class TroopCard : public Card {
private:
    Color color;
    Number number;
public:
    inline TroopCard(Color c, Number n): Card(CardType::TROOP_CARD), color(c), number(n) {}
    
    inline Color getColor() const { return color; }
    inline Number getNumber() const { return number; }
};
