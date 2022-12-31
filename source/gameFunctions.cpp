#include <iostream>
#include <vector>
#include <algorithm>

#include "dataTypes.hpp"

void clearScreen() {
    std::cout << std::endl;
    system("clear");
}

void progressPlayerList(std::vector<Player> &players) {
    std::rotate(players.begin(), players.begin() + 1, players.end());
}