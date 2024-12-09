//
// Created by Maddox Guthrie on 1/22/23.
//

// Class definition
#include "Card.hpp"

// Class functions
Card::Card() = default;

Card::Card(std::string &name) {
    this->name = name;

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
    if (name.find("Skip") != std::string::npos) {
        type = Skip;
    } else if (name.find("Reverse") != std::string::npos) {
        type = Reverse;
    } else if (name.find("Draw Two") != std::string::npos) {
        type = DrawTwo;
    } else if (name.find("Draw Four") != std::string::npos) {
        type = DrawFour;
    } else if (name.find("Wild") != std::string::npos) {
        type = Wild;
    } else {
        type = Number;
    }

    // Set card rank
    if (type == Number) {
        if(isnumber(name.back())) {
            // convert character value to integer representation.
            rank = name.back() - '0';
        } else {
            rank = -1;
        }
    }
}

std::ostream &operator<<(std::ostream &outStream, const Card &card) {
    if (card.color == Red) {
        outStream << "\033[;31m" << card.name << "\033[0m";
    } else if (card.color == Green) {
        outStream << "\033[;32m" << card.name << "\033[0m";
    } else if (card.color == Yellow) {
        outStream << "\033[;33m" << card.name << "\033[0m";
    } else if (card.color == Blue) {
        outStream << "\033[;34m" << card.name << "\033[0m";
    } else {
        outStream << card.name;
    }

    return outStream;
}

bool operator<(Card &lhs, Card rhs) {
    return lhs.getCardColor() < rhs.getCardColor();
}

cardType Card::getCardType() {
    return type;
}

cardColor Card::getCardColor() {
    return color;
}

void Card::sanitizeCard() {
    if (type == Wild || type == DrawFour) {
        color = None;
    }
}

void Card::setWildColor(std::string &colorStr) {
    if (type == Wild || type == DrawFour) {
        if (colorStr == "Red") color = Red;
        if (colorStr == "Yellow") color = Yellow;
        if (colorStr == "Green") color = Green;
        if (colorStr == "Blue") color = Blue;
    }
}

bool Card::checkCardCompatibility(Card &topCard) {
    if (this->type == Wild || this->type == DrawFour) {
        return true;
    }

    if (this->color == topCard.color) {
        return true;
    }

    if (this->type == topCard.type) {
        if(this->type == Number) {
            if(this->rank == topCard.rank) {
                return true;
            } else {
                return false;
            }
        }
        return true;
    }

    return false;
}
