#pragma once
#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <array>
#include "../../server/include/Constants.hpp"
class DrawingCanvasA: public wxPanel {
    public:
        DrawingCanvasA(wxWindow*, wxPoint, wxSize);
        virtual void OnPaint(wxPaintEvent &evt) = 0;
        void FillPocketCards(const std::array<struct Card, pocket_cards>&);
    protected:
        void LoadBasicTemplate();
        wxBitmap FetchCardBitmap(const std::string&);
        virtual void FillStructures() = 0;
        virtual void DrawPocketCards(wxGraphicsContext *gc) = 0;
        std::array<wxBitmap, pocket_cards> pocketCards = {};
        const std::string extension = ".svg.png";
        wxBitmap cardOtherside;
};