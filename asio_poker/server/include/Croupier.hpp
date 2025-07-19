#pragma once
#include <vector>
#include <array>
#include <random>
#include "Constants.hpp"


class Croupier {
    public:
        Croupier();
        std::array<struct Card, 2> GetPocketCards();
        std::array<struct Card, 3> GetFlop();
        struct Card GetTurnCard();
        struct Card GetRiverCard();
        void GenerateDeck();
        void Swap(int i, int j) {
            auto tmp = deck[i];
            deck[i] = deck[j];
            deck[j] = tmp;
        }
    private:
        std::array<struct Card, deck_size> deck;
        std::vector<struct Card> distributed;
        unsigned int usedCards;
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_int_distribution<> dist;

};