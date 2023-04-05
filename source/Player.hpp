//
// Created by Maddox Guthrie on 1/22/23.
//

#ifndef UNO_PLAYER_HPP
#define UNO_PLAYER_HPP

// Standard C++
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Custom data types
#include "dataTypes.hpp"

// Card definition
#include "Card.hpp"

class Player {
private:

    std::vector<Card> playerHand;
    std::string playerName;
    int playerNumberOfCards = 0;

public:
    Player();

    friend std::ostream& operator<<(std::ostream& outStream, const Player& player);
    friend std::istream& operator>>(std::istream& inStream, Player& player);

    void addCards(Card &card);
    void displayPlayerCards();
};

#endif //UNO_PLAYER_HPP