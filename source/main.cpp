// Standard C++

#include <iostream>
#include <fstream>
#include <stack>
#include <algorithm>

// Custom data types and containers
#include "iterable_stack.hpp"
#include "dataTypes.hpp"
#include "Player.hpp"

// Card and game functions
#include "cardFunctions.hpp"
#include "gameFunctions.hpp"

int main(int argc, const char *argv[]) {
    std::cout << "Welcome to Uno_cpp!\nGame Version: v0.0.2 Pre-alpha\n";

    /* Shorthand variable assignment to if statement result.
     * std::ifstream cardFile;
     * if(argc > 1) {
     *      cardFile = argv[1];
     * } else {
     *      cardFile = "cards.txt";
     * }
     */
    std::ifstream cardFile((argc > 1) ? argv[1] : "cards.txt");

    // Check if cardFile is open to read.
    if (!cardFile.is_open()) {
        std::cout << "\033[;31m" << " ERROR: could not open file" << "\033[0m" << std::endl;
        return -1;
    }

    // Create players with checking to prevent < 2
    std::vector<Player> players;
    std::string playerName;
    int numberOfPlayers = 0;
    std::cout << "Enter a players name: ";
    while (std::getline(std::cin, playerName)) {
        if(playerName.empty() && numberOfPlayers < 2) {
            std::cout << "You must have at least 2 players to play\n";
            std::cout << "Enter a players name: ";
        } else if(!playerName.empty()) {
            addPlayers(players, playerName);
            numberOfPlayers++;
        } else if(playerName.empty() && numberOfPlayers >= 2) {
            break;
        }
        clearScreen();
        std::cout << "Enter a players name";
        if(numberOfPlayers >= 2) {
            std::cout << " or press enter to continue: ";
        } else {
            std::cout << ": ";
        }
    }

    // Create and prepare deck
    iterable_stack<Card> deck;
    fillDeck(cardFile, deck, numberOfPlayers);
    shuffleDeck(deck);

    // Give each player their hand
    for (int i = 0; i < 7; i++) {
        for (auto &player: players) {
            player.addCards(deck.top());
            deck.pop();
        }
    }

    // Draw a starting card and create the discard pile
    iterable_stack<Card> discardPile;
    discardPile.push(std::move(deck.top()));
    deck.pop();

    // As per official Uno rules
    if (discardPile.top().getCardType() == DrawFour) {
        deck.push(std::move(discardPile.top()));
        shuffleDeck(deck);
    }

    if (discardPile.top().getCardType() == Wild) {
        std::cout << "Current Player: " << players.front() << "\n";
        setWildColor(discardPile.top());
    }

    clearScreen();

    std::string playerInput;
    while (numberOfPlayers > 1) {
        std::cout << "Current Player: " << players.front() << "\n";
        std::cout << "Current Card: " << discardPile.top() << "\n\n";

        players.front().displayPlayerCards();

        if(players.front().checkPlayability(discardPile.top())) {
            std::cout << "YES!\n";
        } else {
            std::cout << "NO!\n";
        }

        std::exit(1);
    }
}