//
// Created by Maddox Guthrie on 12/31/22.
//

#ifndef UNO_CARDFUNCTIONS_HPP
#define UNO_CARDFUNCTIONS_HPP

#include <vector>
#include <stack>
#include <algorithm>
#include <random>
#include <algorithm>

#include "dataTypes.hpp"

void shuffleDeck(std::stack<Card> &deck) {
    std::vector<Card> tempDeck;
    for(int i = 0; i < deck.size(); i++) {
        tempDeck.push_back(deck.top());
        deck.pop();
    }

    auto rd = std::random_device{};
    auto rng = std::default_random_engine{rd()};
    std::shuffle(tempDeck.begin(), tempDeck.end(), rng);

    for(int i = 0; i < tempDeck.size(); i++) {
        if(deck.top().type == Wild || deck.top().type == DrawFour) {
            deck.top().color = None;
        }
        deck.push(tempDeck.back());
        tempDeck.pop_back();
    }
}

void refreshDeck(std::stack<Card> &deck, std::stack<Card> &discardPile) {
    for(int i = 0; i < discardPile.size(); i++) {
        deck.push(discardPile.top());
        discardPile.pop();
    }
    shuffleDeck(deck);
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

bool cardIsPlayable(Card &playersCard, Card &playCard) {
    // Pass if card type is wild or draw four
    if(playCard.type == Wild || playCard.type == DrawFour) {
        if(playersCard.color == playCard.color) {
            return true;

        }
        return false;

    }

    if(playersCard.name == playCard.name) {
        return true;

    }

    if(playersCard.color == playCard.color && playCard.color != None) {
        return true;

    }

    if(playersCard.type == playCard.type) {
        if (playersCard.type == Number) {
            if (playCard.number == playersCard.number) {
                return true;

            }

        } else if (playersCard.color == playCard.color) {
            return true;

        }
    }

    return false;
}

bool cardsAreEqual(Card &cardOne, Card &cardTwo) {
    if(cardOne.uuid == cardTwo.uuid) {
        return true;

    } else if(cardOne.name == cardTwo.name) {
        return true;

    } else if(cardOne.type == cardTwo.type) {
        if(cardOne.color == cardTwo.color) {
            if(cardOne.number == cardTwo.number) {
                return true;

            }
        }
    }

    return false;
}

cardType getCardType(std::string &name) {
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

Card buildCard(std::string &cardName) {
    Card card;
    card.name = cardName;
    card.color = getCardColor(cardName);
    card.type = getCardType(cardName);
    if(card.type == Number) {
        card.number = getCardNumber(cardName);
    } else {
        card.number = -1;
    }

    return card;
}

#endif //UNO_CARDFUNCTIONS_HPP
