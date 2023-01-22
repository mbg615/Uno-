//
// Created by Maddox Guthrie on 1/22/23.
//

// Class definition
#include "Card.hpp"

// Class functions
void Card::printCard() const {
    if(color == Red) {
        std::cout << "\033[;31m" << name << "\033[0m";
    } else if(color == Green) {
        std::cout << "\033[;32m" << name << "\033[0m";
    } else if(color == Yellow) {
        std::cout << "\033[;33m" << name << "\033[0m";
    } else if(color == Blue) {
        std::cout << "\033[;34m" << name << "\033[0m";
    } else {
        std::cout << name;
    }
}

std::ostream& operator<<(std::ostream& outStream, const Card& card) {
    if(card.color == Red) {
        outStream << "\033[;31m" << card.name << "\033[0m";
    } else if(card.color == Green) {
        outStream << "\033[;32m" << card.name << "\033[0m";
    } else if(card.color == Yellow) {
        outStream << "\033[;33m" << card.name << "\033[0m";
    } else if(card.color == Blue) {
        outStream << "\033[;34m" << card.name << "\033[0m";
    } else {
        outStream << card.name;
    }

    return outStream;
}

int Card::getCardNumber() const {
    return number;
}

boost::uuids::uuid Card::getCardUUID() const {
    return uuid;
}

std::string Card::getCardName() const {
    return name;
}

cardColor Card::getCardColor() const {
    return color;
}

cardType Card::getCardType() const {
    return type;
}