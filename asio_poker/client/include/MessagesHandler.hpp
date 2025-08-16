#pragma once
#include <string>
#include "../../server/include/Constants.hpp"
#include "DebugConsole.hpp"
#include <vector>
#include "Player.hpp"
class EffectManager;
class MessagesHandler {
    public:
        MessagesHandler();
        void ResolveMessage(const std::string&);
        void SetPlayer(Player*);
        std::array<struct Card, pocket_cards> ResolvePocketCardsMessage(const std::string&) const;
        std::array<struct Card, flop_size> ResolveFlopMessage(const std::string&) const;
        struct Card ResolveAnotherCardMessage(const std::string&) const;
        void ResolveKillMessage(const std::string&);
        int ShellId(const std::string&) const;
        void SetDebugger(DebugConsole* db);
        void ResolveAcceptCallMessage(const std::string&);
        void ResolveStakeMessage(const std::string&);
        void ResolvePotMessage(const std::string&);
        void ResolveShowCardsMessage(const std::string&);
        void ResolveSoloWinMessage(const std::string&);
        void ResolveMultiWinMessage(const std::string&);
        std::vector<std::string> GetAllParameters(const std::string& msg) const;
        std::string ShellFirstParameter(const std::string& msg) const;
    private:
        std::vector<std::string> LiftCardsOutOfString(const std::string&) const;
        Player *player;
        EffectManager* effectManager;
        DebugConsole* debugConsole = nullptr;
};

