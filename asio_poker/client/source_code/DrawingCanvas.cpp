#include "../include/DrawingCanvas.hpp"
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
DrawingCanvas::DrawingCanvas(wxWindow* parent, wxWindowID id, const wxPoint &pos, const wxSize &size): wxPanel(parent,id,pos,size) {
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->Bind(wxEVT_PAINT, &DrawingCanvas::OnPaint, this);
    LoadBasicTemplate();
    FillStructures();
}

void DrawingCanvas::OnPaint(wxPaintEvent &evt) {
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

void DrawingCanvas::DrawPocketCards(wxGraphicsContext *gc) {
    for(unsigned int i = 0 ; i< pocket_cards ;++i) gc->DrawBitmap(pocketCards[i],firstCardPosX+i*cardWidth,firstCardPosY,cardWidth,cardHeight);
}

void DrawingCanvas::DrawSharedCards(wxGraphicsContext *gc) {
    for(unsigned int i = 0 ; i< flop_size +extra_cards_size ; ++i) gc->DrawBitmap(sharedCards[i],i*cardWidth,0,cardWidth,cardHeight);
}

void DrawingCanvas::FillStructures() {
    for(unsigned int i = 0 ; i < flop_size +extra_cards_size ; ++i) sharedCards[i] = cardOtherside;
    for(unsigned int i  = 0 ; i< pocket_cards ; ++i) pocketCards[i] = cardOtherside;
}

void DrawingCanvas::LoadBasicTemplate() {
    wxImage image;
    //image.LoadFile("../resources/back.png", wxBITMAP_TYPE_ANY);
    image.LoadFile(resource_dir+ otherside_card_file, wxBITMAP_TYPE_ANY);
    cardOtherside = wxBitmap(image);
}

wxBitmap DrawingCanvas::FetchCardBitmap(const std::string& cardName) {
    wxImage image;
    image.LoadFile(resource_dir+ cardName +extension, wxBITMAP_TYPE_ANY);
    return wxBitmap(image);
}