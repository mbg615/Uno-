//
// Created by xoddam on 12/21/22.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "dataTypes.h"

void shuffleDeck(std::vector<Card> &deck) {
    auto rd = std::random_device{};
    auto rng = std::default_random_engine{rd()};
    std::shuffle(deck.begin(), deck.end(), rng);
}

int getCardNumber(std::string &name) {
    if(name.find('0') != std::string::npos) {
        return 0;
    } else if(name.find('1') != std::string::npos) {
        return 1;
    } else if(name.find('2') != std::string::npos) {
        return 2;
    } else if(name.find('3') != std::string::npos) {
        return 3;
    } else if(name.find('4') != std::string::npos) {
        return 4;
    } else if(name.find('5') != std::string::npos) {
        return 5;
    } else if(name.find('6') != std::string::npos) {
        return 6;
    } else if(name.find('7') != std::string::npos) {
        return 7;
    } else if(name.find('8') != std::string::npos) {
        return 8;
    } else if(name.find('9') != std::string::npos) {
        return 9;
    } else {
        return -1;
    }
}

_type getCardType(std::string &name) {
    if(name.find("Skip") != std::string::npos) {
        return Skip;
    } else if(name.find("Reverse") != std::string::npos) {
        return Reverse;
    } else if(name.find("Draw Two") != std::string::npos) {
        return DrawTwo;
    } else if(name.find("Draw Four") != std::string::npos) {
        return DrawFour;
    } else if(name.find("Wild") != std::string::npos) {
        return Wild;
    } else {
        return Number;
    }
}

_color getCardColor(std::string &name) {
    if (name.find("Red") != std::string::npos) {
        return Red;
    } else if (name.find("Green") != std::string::npos) {
        return Green;
    } else if (name.find("Yellow") != std::string::npos) {
        return Yellow;
    } else if (name.find("Blue") != std::string::npos) {
        return Blue;
    } else {
        return None;
    }
}