#pragma once
#include "Constants.hpp"
#include <array>

class Player {
    public:
        Player(unsigned int);
        //void Pass();
        //void Call();
        //void Raise();
        void AcceptCards(std::array<struct Card, pocket_cards>);
        std::array<struct Card, pocket_cards> GetPocketCards() const;
        unsigned int GetId() const;
    private:
        std::array<struct Card, pocket_cards> cards;
        unsigned int id;

};