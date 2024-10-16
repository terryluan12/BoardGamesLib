#include "DoganGame.h"
#include "DoganExceptions.h"
#include <iostream>

DoganGame::DoganGame(DoganConfig config) : rengine(std::random_device{}()), die(1, 6), board(DoganBoard(config)){
    std::array<size_t, 5> resourceCount = config.getResourceCount();
    std::vector<DevelopmentType> developments = config.getDevelopments(rengine);
    bank = DoganBank(resourceCount, developments);
}

void DoganGame::addPlayer(DoganPlayer p) {
    this->players.push_back(p);
};

void DoganGame::givePlayerDevCard(DoganPlayer p, std::array<size_t, 5> c) {
    if(p.getInventory().canAfford(c)){
        p.getInventory().removeResources(c);
        p.getInventory().addDevelopment(bank.popDevelopment());
    }
    else {
        throw InsufficientResourcesException("Error: Player does not have enough resources to purchase development card");
    }
}

void DoganGame::printBoard(void) {
    std::cout << this->board;
    for(auto & p : this->players) {
        std::cout << p;
    }
    std::cout << this->bank;
}