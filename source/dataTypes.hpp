//
// Created by xoddam on 12/21/22.
//

#ifndef UNO_DATATYPES_HPP
#define UNO_DATATYPES_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Boost
#include <boost/uuid/uuid.hpp>

enum cardColor { Red, Green, Yellow, Blue, None };
enum cardType { Number, Skip, Reverse, DrawTwo, DrawFour, Wild };

class Card {
    public:
        boost::uuids::uuid uuid;
        std::string name;
        cardColor color;
        cardType type;
        int number;

        friend std::ostream& operator<<(std::ostream& outStream, const Card& card) {
            if(card.color == Red) {
                outStream << "\033[;31m" << card.name << "\033[0m";
            } else if(card.color == Green) {
                outStream << "\033[;32m" << card.name << "\033[0m";
            } else if(card.color == Yellow) {
                outStream << "\033[;33m" << card.name << "\033[0m";
            } else if(card.color == Blue) {
                outStream << "\033[;34m" << card.name << "\033[0m";
            } else {
                outStream << card.name;
            }

            return outStream;
        }

        void printCard() const {
            if(color == Red) {
                std::cout << "\033[;31m" << name << "\033[0m";
            } else if(color == Green) {
                std::cout << "\033[;32m" << name << "\033[0m";
            } else if(color == Yellow) {
                std::cout << "\033[;33m" << name << "\033[0m";
            } else if(color == Blue) {
                std::cout << "\033[;34m" << name << "\033[0m";
            } else {
                std::cout << name;
            }
        }
};

class Player {
    private:
        std::vector<Card> playerHand;

    public:
        std::string playerName;
        int playerNumberOfCards = 0;

        void addCards(Card &card) {
            playerHand.push_back(card);
            playerNumberOfCards += 1;
        }

        void addCards(std::vector<Card> &cards) {
            playerHand.insert(playerHand.end(), cards.begin(), cards.end());
            playerNumberOfCards += (int) cards.size();
        }

        void playCard(Card &playersCard) {
            for(int i = 0; i < playerHand.size(); i++) {
                if(playersCard.name == playerHand[i].name) {
                    playerHand.erase(playerHand.begin() + i);
                    break;
                }
            }
        }

        bool playerHasCard(Card &cardToSearchFor) {
            for(Card &card: playerHand) { // Cannot use std::for_each bc it only passes one argument
                if(card.name == cardToSearchFor.name) {
                    return true;
                }
            }
            return false;
        }

        bool playerCanPlay(Card &cardToPlayFrom) {
            for(Card &card: playerHand) {
                // Pass if card type is wild or draw four
                if(card.type == Wild || card.type == DrawFour) {
                    return true;
                }

                if(card.name == cardToPlayFrom.name) {
                    return true;

                }

                if(card.color == cardToPlayFrom.color && cardToPlayFrom.color != None) {
                    return true;

                }

                if(card.type == cardToPlayFrom.type) {
                    if (cardToPlayFrom.type == Number) {
                        if (card.number == cardToPlayFrom.number) {
                            return true;
                        }

                    } else if (card.color == cardToPlayFrom.color) {
                        return true;

                    }
                }
            }

            return false;
        }

        void sortCards() {
            // TODO: Make a better sort function
            std::vector<Card> reds, yellows, greens, blues, others;
            for(auto &card: playerHand) {
                if(card.color == Red) {
                    reds.push_back(std::move(card));
                } else if(card.color == Yellow) {
                    yellows.push_back(std::move(card));
                } else if(card.color == Green) {
                    greens.push_back(std::move(card));
                } else if(card.color == Blue) {
                    blues.push_back(std::move(card));
                } else {
                    others.push_back(std::move(card));
                }

                playerHand.clear();
                playerHand.insert(playerHand.end(), reds.begin(), reds.end());
                playerHand.insert(playerHand.end(), yellows.begin(), yellows.end());
                playerHand.insert(playerHand.end(), greens.begin(), greens.end());
                playerHand.insert(playerHand.end(), blues.begin(), blues.end());
                playerHand.insert(playerHand.end(), others.begin(), others.end());
            }
        }

        void displayPlayerCards() {
            sortCards();
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
};

#endif //UNO_DATATYPES_HPP
