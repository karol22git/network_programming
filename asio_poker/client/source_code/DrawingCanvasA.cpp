#include "../include/DrawingCanvasA.hpp"

DrawingCanvasA::DrawingCanvasA(wxWindow* parent, wxPoint pos, wxSize size) :
    wxPanel(parent, wxID_ANY, pos, size) {
    }

void DrawingCanvasA::LoadBasicTemplate() {
    wxImage image;
    image.LoadFile(resource_dir+ otherside_card_file, wxBITMAP_TYPE_ANY);
    cardOtherside = wxBitmap(image);
}

wxBitmap DrawingCanvasA::FetchCardBitmap(const std::string& cardName) {
    wxImage image;
    image.LoadFile(resource_dir+ cardName +extension, wxBITMAP_TYPE_ANY);
    return wxBitmap(image);
}

void DrawingCanvasA::FillPocketCards(const std::array<struct Card, pocket_cards>& c) {
    for(unsigned int i = 0 ; i <pocket_cards ; ++i) {
        pocketCards[i] = FetchCardBitmap(c[i].toString());
    }
    Refresh();
}