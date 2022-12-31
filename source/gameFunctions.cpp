#include <iostream>

#include "dataTypes.hpp"

void clearScreen() {
    std::cout << std::endl;
    system("clear");
}

void progressPlayerList(Player players[], int len) {
    Player playerStore = players[0];
    for(int i = 0; i < len; i++) {
        players[i] = players[i + 1];
    }
    players[len - 1] = playerStore;
}