// Standard C++
#include <algorithm>
#include <utility>

// Player definition
#include "Player.hpp"

// Class functions
std::ostream &operator<<(std::ostream &outStream, const Player &player) {
    outStream << player.playerName;
    return outStream;
}

std::istream &operator>>(std::istream &inStream, Player &player) {
    inStream >> player.playerName;
    return inStream;
}

Player::Player() = default;

Player::Player(std::string name) {
    this->playerName = std::move(name);
}

void Player::addCards(Card &card) {
    playerHand.push_back(card);
    playerNumberOfCards += 1;
}

void Player::displayPlayerCards() {
    //std::sort(playerHand.begin(), playerHand.end());
    std::cout << playerName << "'s hand:\n";
    // Must be ranged based because we need index
    for (int i = 0; i < playerHand.size(); i++) {
        std::cout << playerHand[i];

        if (i + 1 != playerHand.size()) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

bool Player::checkPlayability(Card &topCard) {
    for (Card &card: playerHand) {
        if (card.checkCardCompatibility(topCard)) {
            std::cout << card << " can be played on " << topCard << "\n";
            return true;
        }
    }
    return false;
}

void Player::drawCard(std::stack<Card> &deck) {
    this->playerHand.push_back(std::move(deck.top()));
    deck.pop();
}
