//
// Created by Maddox Guthrie on 12/31/22.
//

#ifndef UNO_GAMEFUNCTIONS_HPP
#define UNO_GAMEFUNCTIONS_HPP

// Standard C++
#include <iostream>
#include <vector>
#include <algorithm>

// Custom data types and containers
#include "dataTypes.hpp"
#include "iterable_stack.hpp"

void clearScreen() {
    std::cout << std::endl;
    system("clear");
}

void waitUntilInput() {
    std::cout << "[Press Enter to continue]" << std::flush;
    std::getchar();
    std::cout << "\r                         \r" << std::flush;
}

void addPlayers(std::vector<Player> &players, std::string &playerName) {
    players.emplace_back(playerName);
}

void fillDeck(std::ifstream &cardFile, iterable_stack<Card> &deck, int numberOfPlayers) {
    std::string currentCard;

    int i = 0;
    do {
        while (std::getline(cardFile, currentCard)) {
            deck.emplace(currentCard);
        }
        deck.pop();
        cardFile.clear();
        cardFile.seekg(0, std::ifstream::beg);
        i++;
    } while (i < numberOfPlayers / 4);
}

void progressPlayerList(std::vector<Player> &players) {
    std::rotate(players.begin(), players.begin() + 1, players.end());
}

void setWildColor(Card &card) {
    std::cout << "(\033[;31mRed\033[0m, \033[;32mGreen\033[0m, \033[;33mYellow\033[0m, \033[;34mBlue\033[0m\n)";
    std::string colorForWild;
    std::cout << "Choose a color for the card: ";
    std::cin >> colorForWild;
    card.setWildColor(colorForWild);

    while (card.getCardColor() == None) {
        std::cout << "\nSorry that is not a valid color.\n";
        std::cout << "(\033[;31mRed\033[0m, \033[;32mGreen\033[0m, \033[;33mYellow\033[0m, \033[;34mBlue\033[0m\n)";
        std::cout << "Choose a color for the card: ";
        std::cin >> colorForWild;
        card.setWildColor(colorForWild);
    }
}

#endif //UNO_GAMEFUNCTIONS_HPP
