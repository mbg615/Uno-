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
        void addCards(Card &card);
        void addCards(std::vector<Card> &cards);
        void playCard(Card &playersCard);
        void sortCards();
        void displayPlayerCards();

        bool playerHasCard(Card &cardToSearchFor);
        bool playerCanPlay(Card &cardToPlayFrom);
};

#endif //UNO_PLAYER_HPP