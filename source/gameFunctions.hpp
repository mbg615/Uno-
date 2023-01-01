//
// Created by Maddox Guthrie on 12/31/22.
//

#ifndef UNO_GAMEFUNCTIONS_HPP
#define UNO_GAMEFUNCTIONS_HPP

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

#endif //UNO_GAMEFUNCTIONS_HPP
