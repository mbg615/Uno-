//
// Created by Maddox Guthrie on 1/22/23.
//

// Player definition
#include "Player.hpp"

#include <algorithm>

// Class functions
std::ostream& operator<<(std::ostream& outStream, const Player& player) {
    outStream << player.playerName;
    return outStream;
}

std::istream& operator>>(std::istream& inStream, Player& player) {
    inStream >> player.playerName;
    return inStream;
}

Player::Player() = default;

void Player::addCards(Card &card) {
    playerHand.push_back(card);
    playerNumberOfCards += 1;
}

void Player::displayPlayerCards() {
    std::sort(playerHand.begin(), playerHand.end());
    std::cout << playerName << "'s hand:\n";
    // Must be ranged based because we need index
    for(int i = 0; i < playerHand.size(); i++) {
        std::cout << playerHand[i];

        if(i + 1 != playerHand.size()) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}