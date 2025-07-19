#pragma onec
#include "Constants.hpp"
#include <array>

class Player {
    public:
        Player(unsigned int);
        void Pass();
        void Call();
        void Raise();
    private:
        std::array<struct Card, pocket_cards> cards;
        unsigned int id;

};