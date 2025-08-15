#pragma once
#include "DrawingCanvasA.hpp"

class GameStage: public DrawingCanvasA {
    public:
        GameStage(wxWindow*, wxPoint, wxSize);
        void FillFlopCards(const std::array<struct Card, flop_size>&);
        void AddAnotherCard(const struct Card);
    private:
        void FillStructures() override;
        void OnPaint(wxPaintEvent &evt) override;
        void DrawPocketCards(wxGraphicsContext *gc) override;
        void DrawSharedCards(wxGraphicsContext *gc);
        std::array<wxBitmap, flop_size + extra_cards_size> sharedCards = {};
        const int unit = 35;
        const int cardWidth = 2*unit;
        const int cardHeight = 3*unit;
        const int firstCardPosX = 105;
        const int firstCardPosY = 280;
};