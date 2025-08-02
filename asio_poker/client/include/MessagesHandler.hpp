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
        int ShellId(const std::string&) const;
        void SetDebugger(DebugConsole* db);
    private:
        std::vector<std::string> LiftCardsOutOfString(const std::string&) const;
        Player *player;
        EffectManager* effectManager;
        DebugConsole* debugConsole = nullptr;
};

