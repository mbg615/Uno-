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

// Boost
#include <boost/uuid/uuid.hpp>

// Custom data types
#include "../Game/dataTypes.hpp"

class Card {
private:
    boost::uuids::uuid uuid;
    std::string name;
    cardType type;
    cardColor color;
    int rank;

public:
    Card();

    explicit Card(std::string &name, boost::uuids::uuid uuid);

    friend std::ostream &operator<<(std::ostream &outStream, const Card &card);

    friend bool operator==(const Card &lhs, const Card &rhs);

    bool checkCardCompatibility(Card &topCard);

    cardType getCardType();

    cardColor getCardColor();

    void sanitizeCard();

    void setWildColor(std::string &colorStr);
};

#endif //UNO_CARD_HPP
