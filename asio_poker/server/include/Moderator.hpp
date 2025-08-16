#pragma once
#include "Croupier.hpp"
#include "Player.hpp"
#include "TurnManager.hpp"
#include <memory>
#include <vector>

struct GameMetadata {
    int whoCalledRaise = 0;
    int startIndex = 0;
    bool didRaiseOccured = false;
    int stake = 0;
    int totalPot = 0;
    bool didBigBlindOccured = false;
};
class UdpServer;
class Moderator {
    public:
        Moderator(UdpServer*);
        void StartGame();
        void CreateNewPlayer(unsigned int id);
        std::vector<Player*> GetPlayers() const;
        void FetchFlop();
        std::array<struct Card, flop_size> GetFlop() const;
        int WhosTurn() const;
        int CurrentTurn() const;
        bool isWonBySurrender() const;
        int GetLastAlivePlayerId() const;
        void Kill(unsigned int);
        Stage FetchStage() const;
        int WhoCalledRaise() const;
        void CallRaise(int);
        int GetFirstAliveIndex() const;
        int GetLastPlayerId() const;
        bool TurnEndCondition() const;
        void SetUpNextStage();
        void EndGame();
        bool CheckIfPlayerHaveEnouhgtMoney(const unsigned int _id) const;
        void Call(const unsigned int);
        void SmallBlind(const unsigned int);
        void BigBlind(const unsigned int);
        int GetStake() const;
        int GetNewWalletForPlayer(int);
        struct Card GetTurnCard() const;
        struct Card GetRiverCard() const;
        void FetchExtraCards();
        void UpdatePot(int);
        int GetPot() const;
        bool didBigBlindOccured() const;
        bool didRaiseOccured() const;
        std::vector<Player*> FetchAllAlivePlayers() const;
        std::vector<struct Card> CardsToVector() const;
        std::vector<int> GetWinners() const;
    private:
        std::unique_ptr<Croupier> croupier = nullptr;
        std::vector<Player*> players;
        std::array<struct Card, flop_size> flopCards;
        struct Card turnCard;
        struct Card riverCard;
        int currentTurn = 0;
        TurnManager* turnManager;
        Stage currentStage;
        struct GameMetadata gm;
        UdpServer* parent;
};