#include "../include/GameStage.hpp"

GameStage::GameStage(wxWindow* parent, wxPoint pos, wxSize size) : DrawingCanvasA(parent, pos, size) {
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->Bind(wxEVT_PAINT, &GameStage::OnPaint, this);
    LoadBasicTemplate();
    FillStructures();
}


void GameStage::FillStructures() {
    for(unsigned int i = 0 ; i < flop_size +extra_cards_size ; ++i) sharedCards[i] = cardOtherside;
    for(unsigned int i  = 0 ; i< pocket_cards ; ++i) pocketCards[i] = cardOtherside;
}

void GameStage::OnPaint(wxPaintEvent &evt) {
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();
    wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
    gc->SetBrush(*wxWHITE_BRUSH);
    gc->SetPen(wxPen(*wxBLACK,2));
    if(gc) {
        DrawPocketCards(gc);
        DrawSharedCards(gc);
    }
    delete gc;
}


void GameStage::DrawPocketCards(wxGraphicsContext *gc) {
    for(unsigned int i = 0 ; i< pocket_cards ;++i) gc->DrawBitmap(pocketCards[i],firstCardPosX+i*cardWidth,firstCardPosY,cardWidth,cardHeight);
}

void GameStage::DrawSharedCards(wxGraphicsContext *gc) {
    for(unsigned int i = 0 ; i< flop_size + extra_cards_size ; ++i) gc->DrawBitmap(sharedCards[i],i*cardWidth,0,cardWidth,cardHeight);
}

void GameStage::FillFlopCards(const std::array<struct Card, flop_size>& c) {
    for(unsigned int i = 0 ; i <flop_size ; ++i) {
        sharedCards[i] = FetchCardBitmap(c[i].toString());
    }
    Refresh();
}


void GameStage::AddAnotherCard(const struct Card c) {
    static int index = 3;
    sharedCards[index] = FetchCardBitmap(c.toString());
    ++index;
    Refresh();
}
