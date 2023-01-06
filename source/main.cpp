#include <iostream>
#include <stack>

// File I/O
#include <fstream>

// Custom data types
#include "dataTypes.hpp"

// Card and game functions
#include "cardFunctions.hpp"
#include "gameFunctions.hpp"

// Boost
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

int main(int argc, const char *argv[]) {
    std::cout << "Game Version: v0.0.1 Pre-alpha\n";

    // Get player data
    int numberOfPlayers;
    std::cout << "How many players are there?: ";
    std::cin >> numberOfPlayers;
    std::cout << "\n";

    if(numberOfPlayers < 2 || numberOfPlayers > 10) {
        if(numberOfPlayers < 1) {
            std::cout << "Uno++ does not support " << numberOfPlayers << " players";
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

    boost::uuids::random_generator gen;

    while(cardFile) {
        std::getline(cardFile,currentCard);
        deck.push(buildCard(currentCard));
        deck.top().uuid = gen();
    }

    // Remove duplicate card
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

        Card playersCardSelection;

        if(players.front().playerCanPlay(discardPile.top())) {
            bool selectingCard = true;
            std::string playersSelection;
            Card playersSelectionAsCard;

            while(selectingCard) {
                // Read the players input
                std::cout << "\nSelect card or draw: ";
                std::getline(std::cin >> std::ws, playersSelection);
                std::cout << "\n";

                // Parse the players input
                if(playersSelection.find("Draw") == std::string::npos) {
                    break;
                }

                playersSelectionAsCard = buildCard(playersSelection);

                if(!players.front().playerHasCard(playersSelectionAsCard)) {
                    std::cout << "Sorry you do not have that card\n";
                    selectingCard = true;
                } else if(!cardIsPlayable(playersSelectionAsCard, discardPile.top())) {
                    std::cout << "Sorry you cannot play that card\n";
                    selectingCard = true;
                } else {
                    selectingCard = false;
                }
            }

            // Ask player for the new color to play from
            if(playersSelectionAsCard.type == Wild || playersSelectionAsCard.type == DrawFour) {
                std::string newColor;
                std::cout << "What color should we play from?: ";
                std::cin >> newColor;
                playersSelectionAsCard.color = getCardColor(newColor);

            }

            // TODO: Generate a UID for each card to reference cards directly instead of loosely
            discardPile.push(playersSelectionAsCard);
            players.front().playCard(playersSelectionAsCard);

        } else { // Player cannot play and they must draw
            std::cout << "You cannot play any of your cards.\n";
            std::cout << "You will draw a card.\n";

            // TODO: Implement a draw function to prevent draws taking up 2 lines.
            Card drawnCard = deck.top();
            deck.pop();
            std::cout << "You drew a ";
            drawnCard.printCard();
            std::cout << "\n";

            if(cardIsPlayable(drawnCard, discardPile.top())) {
                std::cout << "The ";
                drawnCard.printCard();
                std::cout << " can be played.\n";
                discardPile.push(drawnCard);
                std::cout << "You played the ";
                drawnCard.printCard();
                std::cout << "\n";

            } else { // Players cannot play the card they drew
                std::cout << "You cannot play the ";
                drawnCard.printCard();
                std::cout << "\n";
                players.front().addCards(drawnCard);
                std::cout << "It was added to your hand";

            }
        }

        progressPlayerList(players);
        std::cout << "\n\n\n\n\n\n";
        //clearScreen();

    }
}
