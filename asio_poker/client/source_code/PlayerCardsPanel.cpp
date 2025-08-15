#include "../include/PlayerCardsPanel.hpp"


PlayerCardsPanel::PlayerCardsPanel(wxWindow* parent, wxPoint pos, wxSize size) :
    DrawingCanvasA(parent,pos,size) {
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->Bind(wxEVT_PAINT, &PlayerCardsPanel::OnPaint, this);
    LoadBasicTemplate();
    FillStructures();
}


void PlayerCardsPanel::OnPaint(wxPaintEvent &evt) {
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();
    wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
    if(gc) {
        PaintRectangles(gc);
        DrawPocketCards(gc);
    }
    delete gc;
}


void PlayerCardsPanel::PaintRectangles(wxGraphicsContext *gc) {
    gc->SetBrush(*wxTRANSPARENT_BRUSH);
    gc->SetPen(wxPen(wxColour(0, 0, 0), 2));
    gc->DrawRectangle(0, 0, 2*unit, 3*unit); 
    gc->DrawRectangle(2*unit, 0,2*unit, 3*unit); 
}
void PlayerCardsPanel::FillStructures() {
    for(unsigned int i  = 0 ; i< pocket_cards ; ++i) pocketCards[i] = cardOtherside;
}

void PlayerCardsPanel::DrawPocketCards(wxGraphicsContext *gc) {
    gc->SetBrush(*wxWHITE_BRUSH);
    gc->SetPen(wxPen(*wxBLACK,2));
    for(unsigned int i = 0 ; i< pocket_cards ;++i) gc->DrawBitmap(pocketCards[i],firstCardPosX+i*cardWidth,firstCardPosY,cardWidth,cardHeight);
}