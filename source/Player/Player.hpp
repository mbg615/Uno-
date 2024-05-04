//
// Created by Maddox Guthrie on 1/22/23.
//

#ifndef UNO_PLAYER_HPP
#define UNO_PLAYER_HPP

// Standard C++
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

// Custom data types
#include "../Game/dataTypes.hpp"

// Card definition
#include "../Card/Card.hpp"

class Player {
private:
    std::vector<Card> playerHand;
    std::string playerName;
    int playerNumberOfCards = 0;

public:
    Player();

    explicit Player(std::string name);

    friend std::ostream &operator<<(std::ostream &outStream, const Player &player);

    friend std::istream &operator>>(std::istream &inStream, Player &player);

    void addCards(Card &card);

    void displayPlayerCards();

    void drawCard(std::stack<Card> &deck);

    bool checkPlayability(Card &topCard);

    Card* findCard(std::string &chosenCard);
};

#endif //UNO_PLAYER_HPP