#include "../include/TurnManager.hpp"

TurnManager::TurnManager(std::vector<Player*>& pList) : players(pList), nextId(-1) {}

int TurnManager::GetNextTurn() {
    int size = quorum;
    for(int i = 1 ;i <=quorum ; ++i) {
        if(players[(nextId + i)%size]->isAlive()) {
            nextId = (nextId +i)% size;
            return nextId;
        }
    }
    return 0;
}

int TurnManager::CurrentTurn() const {
    if(nextId == -1) return 0;
    else return nextId;
}