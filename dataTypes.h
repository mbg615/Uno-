//
// Created by xoddam on 12/21/22.
//

#ifndef UNO_DATATYPES_H
#define UNO_DATATYPES_H

#include <iostream>
#include <string>
#include <vector>

enum _color { Red, Green, Yellow, Blue, None };
enum _type { Number, Skip, Reverse, DrawTwo, DrawFour, Wild };

typedef struct _card {
    std::string name;
    _color color;
    _type type;
    int number;
} Card;

class Player {
    private:
        std::vector<Card> playerHand;

    public:
        int playerNumber;
        std::string playerName;
        int playerNumberOfCards = 0;

        void addCards(Card card) {
            playerHand.push_back(card);
            playerNumberOfCards += 1;
        }

        void addCards(std::vector<Card> cards) {
            playerHand.insert(playerHand.end(), cards.begin(), cards.end());
            playerNumberOfCards += cards.size();
        }

        void displayPlayerCards() {
            std::cout << playerName << "'s hand:\n";
            for(int i = 0; i < playerHand.size(); i++) {
                if(playerHand[i].color == Red) {
                    std::cout << "\033[;31m" << playerHand[i].name << "\033[0m";
                } else if(playerHand[i].color == Green) {
                    std::cout << "\033[;32m" << playerHand[i].name << "\033[0m";
                } else if(playerHand[i].color == Yellow) {
                    std::cout << "\033[;33m" << playerHand[i].name << "\033[0m";
                } else if(playerHand[i].color == Blue) {
                    std::cout << "\033[;34m" << playerHand[i].name << "\033[0m";
                } else {
                    std::cout << playerHand[i].name;
                }

                if(i + 1 != playerHand.size()) {
                    std::cout << ", ";
                }
            }
            std::cout << "\n";
        }

        void displayPlayerCardsNoColor() {
            std::cout << playerName << "'s hand:\n";
            for(int i = 0; i < playerHand.size(); i++) {
                std::cout << playerHand[i].name;
                if(i + 1 != playerHand.size()) {
                    std::cout << ", ";
                }
            }
            std::cout << "\n";
        }

};

#endif //UNO_DATATYPES_H
