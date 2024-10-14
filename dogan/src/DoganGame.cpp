#include "DoganGame.h"
#include <iostream>

void DoganGame::addPlayer(DoganPlayer p) {
    this->players.push_back(p);
};


void DoganGame::printBoard(void) {
    std::cout << this->board;
    for(auto & p : this->players) {
        std::cout << p;
    }
}