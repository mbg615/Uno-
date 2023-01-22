//
// Created by Maddox Guthrie on 1/22/23.
//

// Player definition
#include "Player.hpp"

// Class functions
void Player::addCards(Card &card) {
    playerHand.push_back(card);
    playerNumberOfCards += 1;
}

void Player::addCards(std::vector<Card> &cards) {
    playerHand.insert(playerHand.end(), cards.begin(), cards.end());
    playerNumberOfCards += (int) cards.size();
}

void Player::playCard(Card &playersCard) {
    for(int i = 0; i < playerHand.size(); i++) {
        if(playersCard.getCardUUID() == playerHand[i].getCardUUID()) {
            playerHand.erase(playerHand.begin() + i);
            break;
        }
    }
}

bool Player::playerHasCard(Card &cardToSearchFor) {
    for(Card &card: playerHand) { // Cannot use std::for_each bc it only passes one argument
        if(card.getCardName() == cardToSearchFor.getCardName()) {
            return true;
        }
    }
    return false;
}

bool Player::playerCanPlay(Card &cardToPlayFrom) {
    for(Card &card: playerHand) {
        // Pass if card type is wild or draw four
        if(card.getCardType() == Wild || card.getCardType() == DrawFour) {
            return true;
        }

        if(card.getCardName() == cardToPlayFrom.getCardName()) {
            return true;

        }

        if(card.getCardColor() == cardToPlayFrom.getCardColor() && cardToPlayFrom.getCardColor() != None) {
            return true;

        }

        if(card.getCardType() == cardToPlayFrom.getCardType()) {
            if (cardToPlayFrom.getCardType() == Number) {
                if (card.getCardNumber() == cardToPlayFrom.getCardNumber()) {
                    return true;
                }

            } else if (card.getCardColor() == cardToPlayFrom.getCardColor()) {
                return true;

            }
        }
    }

    return false;
}

void Player::displayPlayerCards() {
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