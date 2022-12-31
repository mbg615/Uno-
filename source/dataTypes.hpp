//
// Created by xoddam on 12/21/22.
//

#ifndef UNO_DATATYPES_HPP
#define UNO_DATATYPES_HPP

#include <iostream>
#include <string>
#include <vector>

enum _color { Red, Green, Yellow, Blue, None };
enum _type { Number, Skip, Reverse, DrawTwo, DrawFour, Wild };

class Card {
    public:
        std::string name;
        _color color;
        _type type;
        int number;

        void printCard() {
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
        int playerNumber;
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

        bool hasCard(std::string possibleCard) {
            for(int i = 0; i < playerHand.size(); i++) {
                if(playerHand[i].name == possibleCard) {
                    return true;
                }
            }
            return false;
        }

        void displayPlayerCards() {
            std::cout << playerName << "'s hand:\n";
            for(int i = 0; i < playerHand.size(); i++) {
                playerHand[i].printCard();

                if(i + 1 != playerHand.size()) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
};

#endif //UNO_DATATYPES_HPP
