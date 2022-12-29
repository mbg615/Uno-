#include <iostream>
#include <vector>

// File I/O
#include <fstream>

// Custom data types
#include "dataTypes.h"

int main() {
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

    Player players[numberOfPlayers];

    for(int i = 0; i < numberOfPlayers; i++) {
        clearScreen();
        std::cout << "What is player " << i + 1 << "'s name? ";
        std::cin >> players[i].playerName;
        players[i].playerNumber = i;
    }

    // Open Card File
    std::ifstream cardFile;
    cardFile.open("cards.txt");

    // Read each card into the deck vector
    // TODO: Implement the deck as a std::stack
    std::vector<Card> deck;
    std::string currentCard;
    while(cardFile) {
        std::getline(cardFile,currentCard);
        Card nextCard;
        nextCard.name = currentCard;
        nextCard.color = getCardColor(currentCard);
        nextCard.type = getCardType(currentCard);
        if(nextCard.type == Number) {
            nextCard.number = getCardNumber(currentCard);
        } else {
            nextCard.number = -1;
        }
        deck.push_back(nextCard);
    }

    // Remove empty space in deck
    deck.pop_back();

    // Shuffle the deck
    void shuffleDeck(std::vector<Card> &deck);
    shuffleDeck(deck);

    // Give each player their hand
    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < numberOfPlayers; j++) {
            players[j].addCards(deck.back());
            deck.pop_back();
        }
    }

    clearScreen();

    std::vector<Card> discardPile;
    Card activeCard = deck.back();
    deck.pop_back();
    discardPile.push_back(activeCard);
    while(numberOfPlayers > 1) {

    }
}


