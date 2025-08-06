#pragma once
#include "Player.hpp"
#include "Constants.hpp"
#include <vector>
class TurnManager {
    public:
        TurnManager(std::vector<Player*>&);
        int GetNextTurn();
        int CurrentTurn() const;
    private:
    int nextId;
    std::vector<Player*> players;
};