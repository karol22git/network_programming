#pragma once
#include "Player.hpp"
#include "Constants.hpp"
#include <vector>
class TurnManager {
    public:
        TurnManager(std::vector<Player*>&);
        int GetNextTurn();
    private:
    int nextId;
    std::vector<Player*> players;
};