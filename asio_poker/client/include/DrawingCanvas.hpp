#pragma once
#include <wx/wx.h>
#include "../../server/include/Constants.hpp"
#include <array>
#include <string>
class DrawingCanvas: public wxPanel {
    public:
        DrawingCanvas(wxWindow* parent, wxWindowID id, const wxPoint &pos, const wxSize &size);
        virtual ~DrawingCanvas(){}
        void FillPocketCards(const std::array<struct Card, pocket_cards>&);
        void FillFlopCards(const std::array<struct Card, flop_size>&);
        void AddAnotherCard(const struct Card);
        void UpdatePot(int);
    private:
        const std::string extension = ".svg.png";
        std::string s;
        wxBitmap cardOtherside;
        const int unit = 35;
        const int cardWidth = 2*unit;
        const int cardHeight = 3*unit;
        const int firstCardPosX = 105;
        const int firstCardPosY = 280;
        int pot;
        void OnPaint(wxPaintEvent &evt);
        void DrawPocketCards(wxGraphicsContext *gc);
        void DrawSharedCards(wxGraphicsContext *gc);
        //void DrawThePot(wxGraphicsContext *gc);
        void FillStructures();
        void LoadBasicTemplate();
        //void FillPocketCards(const std::array<struct Card, pocket_cards>&);
        //void FillFlopCards(const std::array<struct Card, flop_size>&);
        //void AddAnotherCard(const struct Card);
        wxBitmap FetchCardBitmap(const std::string&);
        std::array<wxBitmap, pocket_cards> pocketCards = {};
        std::array<wxBitmap, flop_size + extra_cards_size> sharedCards = {};
};