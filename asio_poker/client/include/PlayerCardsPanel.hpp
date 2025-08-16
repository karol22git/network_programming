#pragma once
#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <array>
#include "../../server/include/Constants.hpp"
#include "DrawingCanvasA.hpp"
class PlayerCardsPanel: public DrawingCanvasA {
    public:
        PlayerCardsPanel(wxWindow*, wxPoint, wxSize);
        void FillPocketCards(struct Card& c1, struct Card& c2);
    private:
        void OnPaint(wxPaintEvent &evt) override;
        void FillStructures() override;
        void DrawPocketCards(wxGraphicsContext *gc) override;
        void PaintRectangles(wxGraphicsContext *gc);
        std::array<wxBitmap, pocket_cards> pocketCards = {};
        int unit = 31;
        const int cardWidth = 2*unit;
        const int cardHeight = 3*unit;
        const int firstCardPosX = 0;
        const int firstCardPosY = 0;
};
