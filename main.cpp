#include <iostream>
#include <vector>

// File I/O
#include <fstream>

// Custom data types
#include "dataTypes.h"

int main() {
    _color getCardColor(std::string name);
    _type getCardType(std::string name);
    int getCardNumber(std::string name);

    std::cout << "Initializing Uno++\n";

    // Get player data
    int numberOfPlayers;
    std::cout << "How many players are there?: ";
    std::cin >> numberOfPlayers;
    std::cout << "\n";

    Player players[numberOfPlayers];

    for(int i = 0; i < numberOfPlayers; i++) {
        std::cout << "What is player " << i + 1 << "'s name? ";
        std::cin >> players[i].playerName;
        players[i].playerNumber = i;
    }

    // Open Card File
    std::ifstream cardFile;
    cardFile.open("cards.txt");

    // Read each card into the deck vector
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

    for(int i = 0; i < numberOfPlayers; i++) {
        players[i].displayPlayerCards();
    }
}


