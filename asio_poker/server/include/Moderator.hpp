#pragma once
#include "Croupier.hpp"
#include "Player.hpp"
#include <memory>
#include <vector>
class Moderator {
    public:
        Moderator();
        void StartGame();
        void CreateNewPlayer(unsigned int id);
        std::vector<Player*> GetPlayers() const;
    private:
        std::unique_ptr<Croupier> croupier = nullptr;
        std::vector<Player*> players;
};