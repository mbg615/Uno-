#include <iostream>
#include <vector>
#include <stack>

// File I/O
#include <fstream>

// Custom data types
#include "dataTypes.hpp"

int main(int argc, const char *argv[]) {
    _color getCardColor(std::string &name);
    _type getCardType(std::string &name);
    int getCardNumber(std::string &name);
    void clearScreen();

    std::cout << "Game Version: v0.0.1 Pre-alpha\n";

    // Get player data
    int numberOfPlayers;
    std::cout << "How many players are there?: ";
    std::cin >> numberOfPlayers;
    std::cout << "\n";

    if(numberOfPlayers < 2 || numberOfPlayers > 10) {
        if(numberOfPlayers == 0) {
            std::cout << "Uno++ does not support 0 players";
        } else if(numberOfPlayers == 1) {
            std::cout << "Uno++ does not support 1 player";
        } else {
            std::cout << "Uno++ does not currently support " << numberOfPlayers << " players" << std::endl;
        }
        exit(-1);
    }

    std::vector<Player> players;
    std::string playerName;
    for(int i = 0; i < numberOfPlayers; i++) {
        clearScreen();
        std::cout << "What is player " << i + 1 << "'s name? ";
        std::cin >> playerName;
        players.emplace_back();
        players.back().playerName = playerName;
        players.back().playerNumber = i;
    }

    // Open Card File
    std::ifstream cardFile;
    if(argc > 1) {
        cardFile.open(argv[1]);
    } else {
        cardFile.open("cards.txt");
    }

    // Read each card into the deck vector
    std::stack<Card> deck;
    std::string currentCard;
    while(cardFile) {
        std::getline(cardFile,currentCard);
        deck.emplace();
        deck.top().name = currentCard;
        deck.top().color = getCardColor(currentCard);
        deck.top().type = getCardType(currentCard);
        if(deck.top().type == Number) {
            deck.top().number = getCardNumber(currentCard);
        } else {
            deck.top().number = -1;
        }
    }

    // Remove empty space in deck
    deck.pop();

    // Shuffle the deck
    void shuffleDeck(std::stack<Card> &deck);
    shuffleDeck(deck);

    // Give each player their hand
    for(int i = 0; i < 7; i++) {
        for(auto & player : players) {
            player.addCards(deck.top());
            deck.pop();
        }
    }

    clearScreen();

    // Draw a starting card and create the discard pile
    std::stack<Card> discardPile;
    discardPile.push(deck.top());
    deck.pop();

    void progressPlayerList(std::vector<Player> &players);

    while(numberOfPlayers > 1) {
        std::cout << "Current Player: " << players.front().playerName << "\n";
        std::cout << "Card to play from: ";
        discardPile.top().printCard();
        std::cout << "\n";

        std::cout << "\n\n";
        players.front().displayPlayerCards();

        std::string cardToPlay;
        std::cout << "\nSelect a card to play: ";
        std::getline(std::cin >> std::ws, cardToPlay);
        std::cout << "\n";

        while(!players.front().hasCard(cardToPlay)) {
            std::cout << "Sorry you do not have that card please select a card you have in your hand.\n";
            std::cout << "Type card to play: ";
            std::getline(std::cin >> std::ws, cardToPlay);
            std::cout << "\n";
        }



        progressPlayerList(players);

    }
}


