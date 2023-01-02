#include <iostream>
#include <stack>

// File I/O
#include <fstream>

// Custom data types
#include "dataTypes.hpp"

// Card and game functions
#include "cardFunctions.hpp"
#include "gameFunctions.hpp"

int main(int argc, const char *argv[]) {
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
        deck.push(buildCard(currentCard));
    }

    // Remove empty space in deck
    deck.pop();

    // Shuffle the deck
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
    // As per official Uno rules
    if(discardPile.top().type == DrawFour) {
        deck.push(discardPile.top());
        discardPile.pop();
        shuffleDeck(deck);
    }

    while(numberOfPlayers > 1) {
        if(deck.empty()) {
            refreshDeck(deck, discardPile);
        }

        std::cout << "Current Player: " << players.front().playerName << "\n";
        std::cout << "Card to play from: ";
        discardPile.top().printCard();
        std::cout << "\n\n";
        players.front().displayPlayerCards();

        Card playersCard;

        if(players.front().hasCardsToPlay(discardPile.top())) {
            std::string cardToPlay;
            std::cout << "\nSelect a card to play or select Draw: ";
            std::getline(std::cin >> std::ws, cardToPlay);
            std::cout << "\n";

            while(!players.front().hasCard(cardToPlay) || cardToPlay.find("Draw") == std::string::npos) {
                std::cout << "Sorry you do not have that card please select a card you have in your hand.\n";
                std::cout << "Select a card to play or select Draw: ";
                std::getline(std::cin >> std::ws, cardToPlay);
                std::cout << "\n";
            }

            playersCard = buildCard(cardToPlay);

            while(!cardIsPlayable(playersCard, discardPile.top())) {
                std::cout << "The card ";
                playersCard.printCard();
                std::cout << " cannot be played.\n";
                std::cout << "Select a card to play or select Draw: ";
                std::getline(std::cin >> std::ws, cardToPlay);
                playersCard = buildCard(cardToPlay);
            }
        } else {
            std::cout << "You do not have any cards you can play, you will draw a card.\n";
            std::cout << "You drew ";
            Card drawnCard = deck.top();
            deck.pop();

            drawnCard.printCard();

            if(cardIsPlayable(drawnCard, discardPile.top())) {
                std::cout << "You can and will play the card\n";
                discardPile.push(drawnCard);
            } else {
                std::cout << "You cannot play this card, it was added to your hand.\n";
                players.front().addCards(drawnCard);
            }
        }

        if(playersCard.type == Wild || playersCard.type == DrawFour) {
            std::cout << "What color would you like to set?: ";
            std::string newColor;
            std::cin >> newColor;
            playersCard.color = getCardColor(newColor);
        }

        discardPile.push(playersCard);
        players.front().playCard(playersCard);

        progressPlayerList(players);
        clearScreen();

    }
}
