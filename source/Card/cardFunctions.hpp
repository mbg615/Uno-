//
// Created by Maddox Guthrie on 12/31/22.
//

#ifndef UNO_CARDFUNCTIONS_HPP
#define UNO_CARDFUNCTIONS_HPP

#include <vector>
#include <stack>
#include <deque>
#include <algorithm>
#include <random>
#include <algorithm>

#include "../Game/dataTypes.hpp"

void shuffleDeck(iterable_stack<Card> &deck) {
    auto rd = std::random_device{};
    auto rng = std::default_random_engine{rd()};
    std::shuffle(deck.begin(), deck.end(), rng);

}

void refreshDeck(iterable_stack<Card> &deck, iterable_stack<Card> &discardPile) {
    for (int i = 0; i < discardPile.size(); i++) {
        deck.push(discardPile.top());
        discardPile.pop();
    }
    shuffleDeck(deck);
}

cardType getCardType(std::string &name) {
    if (name.find("Skip") != std::string::npos) {
        return Skip;
    } else if (name.find("Reverse") != std::string::npos) {
        return Reverse;
    } else if (name.find("Draw Two") != std::string::npos) {
        return DrawTwo;
    } else if (name.find("Draw Four") != std::string::npos) {
        return DrawFour;
    } else if (name.find("Wild") != std::string::npos) {
        return Wild;
    } else {
        return Number;
    }
}

cardColor getCardColor(std::string &name) {
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

Card drawCard(std::stack<Card> &deck) {
    Card drawnCard = deck.top();
    deck.pop();
    return std::move(drawnCard);
}

void playCard(iterable_stack<Card> &discardPile, Card &cardToPlay) {
    if(cardToPlay.getCardType() != Number) {
        switch (cardToPlay.getCardType()) {
            case Skip:
                break;

            case Reverse:
                break;

            case DrawTwo:
                break;

            case DrawFour:
                break;

            case Wild:
                break;

            default:
                break;
        }
        discardPile.push(cardToPlay);
    }
}

#endif //UNO_CARDFUNCTIONS_HPP
