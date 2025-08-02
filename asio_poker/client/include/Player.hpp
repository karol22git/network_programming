#pragma once
#include <array>
#include "../../server/include/Constants.hpp"
class DrawingCanvas;
class Player {
    public:
        static void Init(unsigned int id);
        static Player& GetInstance();
        Player(const Player&) = delete;
        Player& operator=(const Player&) = delete;
        void Pass();
        void Raise();
        void Call();
        void SetPocketCards(const std::array<struct Card, pocket_cards>&);
        void SetFlopCards(const std::array<struct Card, flop_size>&);
        void AddExtraCard(const struct Card&);
        unsigned int GetId() const;
    private:
        Player(unsigned int);
        int id;
        unsigned int index;
        std::array<Card, pocket_cards> pocketCards;
        std::array<struct Card, flop_size> flopCards;
        std::array<struct Card, extra_cards_size> extraCards;
        DrawingCanvas* drawingCanvas;
        static Player* instance;

};