#pragma once
#include "Croupier.hpp"
#include "Player.hpp"
#include "TurnManager.hpp"
#include <memory>
#include <vector>
class Moderator {
    public:
        Moderator();
        void StartGame();
        void CreateNewPlayer(unsigned int id);
        std::vector<Player*> GetPlayers() const;
        void FetchFlop();
        std::array<struct Card, flop_size> GetFlop() const;
        int WhosTurn() const;
        bool isWonBySurrender() const;
        int GetLastAlivePlayerId() const;
        void Kill(unsigned int);
    private:
        std::unique_ptr<Croupier> croupier = nullptr;
        std::vector<Player*> players;
        std::array<struct Card, flop_size> flopCards;
        int currentTurn = 0;
        TurnManager* turnManager;
};