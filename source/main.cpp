// Standard C++
#include <iostream>
#include <stack>
#include <fstream>
#include <algorithm>

// Custom data types
#include "dataTypes.hpp"
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

    // Get player data
    int numberOfPlayers;
    std::cout << "How many players are there?: ";
    std::cin >> numberOfPlayers;
    std::cout << "\n";

    if (numberOfPlayers < 2 || numberOfPlayers > 10) {
        if (numberOfPlayers < 1) {
            std::cout << "Uno++ does not support " << numberOfPlayers << " players";
        } else if (numberOfPlayers == 1) {
            std::cout << "Uno++ does not support 1 player";
        } else {
            std::cout << "Uno++ does not currently support " << numberOfPlayers << " players" << std::endl;
        }
        return -1;
    }

    std::vector<Player> players;
    std::string playerName;
    for (int i = 0; i < numberOfPlayers; i++) {
        players.emplace_back();
        std::cout << "What is player " << i + 1 << "'s name? ";
        std::cin >> players.back();
    }

    std::stack<Card> deck;
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
    std::stack<Card> discardPile;
    discardPile.push(std::move(deck.top()));

    // As per official Uno rules
    if (discardPile.top().getCardType() == DrawFour) {
        deck.push(std::move(discardPile.top()));
        shuffleDeck(deck);
    }

    while (numberOfPlayers > 1) {
        std::cout << "Current Player: " << players.front() << "\n";
        players.front().displayPlayerCards();


        if (deck.empty()) {
            refreshDeck(deck, discardPile);
        }








        progressPlayerList(players);
    }
}