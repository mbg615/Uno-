// Standard C++
#include <iostream>
#include <stack>
#include <fstream>
#include <algorithm>

// Custom data types and containers
#include "dataTypes.hpp"
#include "iterable_stack.hpp"
#include "Player.hpp"

// Card and game functions
#include "cardFunctions.hpp"
#include "gameFunctions.hpp"

// Boost
#include <boost/uuid/uuid_generators.hpp>

int main(int argc, const char *argv[]) {
    std::cout << "Game Version: v0.0.1 Pre-alpha\n";

    // Open Card File
    std::ifstream cardFile((argc > 1) ? argv[1] : "cards.txt");

    if (!cardFile.is_open()) {
        std::cout << "\033[;31m" << " ERROR: could not open file" << "\033[0m" << std::endl;
        return -1;
    }

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
        std::cout << "Enter a players name";
        if(numberOfPlayers >= 2) {
            std::cout << " or press enter to continue: ";
        } else {
            std::cout << ": ";
        }
    }

    for (Player &player: players) {
        std::cout << player << "\n";
    }


//    for (int i = 0; i < numberOfPlayers; i++) {
//        players.emplace_back();
//        std::cout << "What is player " << i + 1 << "'s name? ";
//        std::cin >> players.back();
//    }

        iterable_stack<Card> deck;

        //std::stack<Card> deck;
        std::string currentCard;
        boost::uuids::random_generator uuidGen;


        // Read each card into the deck vector
        while (std::getline(cardFile, currentCard)) {
            deck.emplace(currentCard, uuidGen());
        }
        // Remove duplicate card
        deck.pop();

        // Shuffle the deck
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
            std::cout << "(\033[;31mRed\033[0m, \033[;32mGreen\033[0m, \033[;33mYellow\033[0m, \033[;34mBlue\033[0m)";
            setWildColor(discardPile.top());
        }

        clearScreen();

        while (numberOfPlayers > 1) {
            std::cout << "Current Player: " << players.front() << "\n";
            std::cout << "Top Card: " << discardPile.top() << "\n\n";

            players.front().displayPlayerCards();

            if (deck.empty()) {
                refreshDeck(deck, discardPile);
            }

            // If player cannot play any card
            if (!players.front().checkPlayability(discardPile.top())) {
                std::cout << "Cannot Play!\n";
                exit(-1);

            } else {
                std::string playerResponse;
                std::cout << "Choose a card to play, or type \"Draw\" to draw a card. ";
                std::cin >> playerResponse;

                if (playerResponse != "Draw") {

                }


            }

            progressPlayerList(players);
        }
    }