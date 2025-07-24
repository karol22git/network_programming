#pragma once
#include <array>
#include "../../server/include/Constants.hpp"
class Player {
    public:
        Player(unsigned int);
        void Pass();
        void Raise();
        void Call();
        void SetPocketCards(const std::array<struct Card, pocket_cards>&);
        void SetFlopCards(const std::array<struct Card, flop_size>&);
        void AddExtraCard(const struct Card&);
    private:
        unsigned int id;
        unsigned int index;
        std::array<Card, pocket_cards> pocketCards;
        std::array<struct Card, flop_size> flopCards;
        std::array<struct Card, extra_cards_size> extraCards;
};