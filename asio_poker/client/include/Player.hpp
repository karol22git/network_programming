#pragma once
#include <array>
#include "../../server/include/Constants.hpp"
class Player {
    public:
        void Pass();
        void Raise();
        void Call();
    private:
        std::array<Card, pocket_cards> cards;
};