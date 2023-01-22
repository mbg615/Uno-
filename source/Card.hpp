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
#include "dataTypes.hpp"

class Card {
    private:
        boost::uuids::uuid uuid;
        std::string name;
        cardColor color;
        cardType type;
        int number;

    public:
        friend std::ostream& operator<<(std::ostream& outStream, const Card& card);

        void printCard() const;

        int getCardNumber() const;

        boost::uuids::uuid getCardUUID() const;

        std::string getCardName() const;

        cardColor getCardColor() const;
        cardType getCardType() const;

};

#endif //UNO_CARD_HPP
