//
// Created by Maddox Guthrie on 1/22/23.
//

#ifndef UNO_CARD_HPP
#define UNO_CARD_HPP

// Standard C++
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Custom data types
#include "../Game/dataTypes.hpp"

class Card {
private:
    std::string name;
    cardType type;
    cardColor color;
    int rank;

public:
    Card();

    explicit Card(std::string &name);

    friend std::ostream &operator<<(std::ostream &outStream, const Card &card);

    friend bool operator==(const Card &lhs, const Card &rhs);

    bool checkCardCompatibility(Card &topCard);

    cardType getCardType();

    cardColor getCardColor();

    void sanitizeCard();

    void setWildColor(std::string &colorStr);
};

#endif //UNO_CARD_HPP
