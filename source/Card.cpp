//
// Created by Maddox Guthrie on 1/22/23.
//

// Class definition
#include "Card.hpp"

// Class functions
Card::Card() = default;

Card::Card(std::string &name, boost::uuids::uuid uuid) {
    this->name = name;
    this->uuid = uuid;

    // Set card color
    if (name.find("Red") != std::string::npos) {
        color = Red;
    } else if (name.find("Green") != std::string::npos) {
        color = Green;
    } else if (name.find("Yellow") != std::string::npos) {
        color = Yellow;
    } else if (name.find("Blue") != std::string::npos) {
        color = Blue;
    } else {
        color = None;
    }

    // Set card type
    if(name.find("Skip") != std::string::npos) {
        type = Skip;
    } else if(name.find("Reverse") != std::string::npos) {
        type = Reverse;
    } else if(name.find("Draw Two") != std::string::npos) {
        type = DrawTwo;
    } else if(name.find("Draw Four") != std::string::npos) {
        type = DrawFour;
    } else if(name.find("Wild") != std::string::npos) {
        type = Wild;
    } else {
        type = Number;
    }

    // Set card number
    if(type == Number) {
        if(name.find('0') != std::string::npos) {
            number = 0;
        } else if(name.find('1') != std::string::npos) {
            number = 1;
        } else if(name.find('2') != std::string::npos) {
            number = 2;
        } else if(name.find('3') != std::string::npos) {
            number = 3;
        } else if(name.find('4') != std::string::npos) {
            number = 4;
        } else if(name.find('5') != std::string::npos) {
            number = 5;
        } else if(name.find('6') != std::string::npos) {
            number = 6;
        } else if(name.find('7') != std::string::npos) {
            number = 7;
        } else if(name.find('8') != std::string::npos) {
            number = 8;
        } else if(name.find('9') != std::string::npos) {
            number = 9;
        } else {
            number = -1;
        }
    } else {
        number = -1;
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

bool operator<(Card &lhs, Card rhs){
    return lhs.getCardColor() < rhs.getCardColor();
}

bool operator==(const Card &lhs, const Card &rhs) {
    if(lhs.uuid == rhs.uuid) {
        return true;
    }

    return false;
}

cardType Card::getCardType() {
    return type;
}

cardColor Card::getCardColor() {
    return color;
}

void Card::sanitizeCard() {
    if(type == Wild || type == DrawFour) {
        color = None;
    }
}
