#include "../include/StatusPanel.hpp"

StatusPanel::StatusPanel(wxWindow* parent,  wxPoint pos, wxSize size, const std::string& _nickname)
    : InfoPanel(parent, pos, size)
{

   // wxGridSizer* grid = new wxGridSizer(3, 2, 0, 0); // odstępy między komórkami

    //nicknameLabel = new wxStaticText(this, wxID_ANY, "Nickname:");
    //nickname = new wxStaticText(this, wxID_ANY, "john deer");
//
    //statusLabel = new wxStaticText(this, wxID_ANY, "Status:");
    //status = new wxStaticText(this, wxID_ANY, _status);//"in game");
//
    //stakeLabel = new wxStaticText(this, wxID_ANY, "Stake:");
    //stake = new wxStaticText(this, wxID_ANY, "100");
    CreateItems( _nickname);
    Arrange();
    //grid->Add(nicknameLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
    //grid->Add(nickname, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
//
    //grid->Add(statusLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
    //grid->Add(status, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
//
    //grid->Add(stakeLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
    //grid->Add(stake, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
   //// SetBackgroundColour(*wxRED);
    SetSizerAndFit(grid);
}

void StatusPanel::CreateItems(const std::string& _nickname) {
    nicknameLabel = new wxStaticText(this, wxID_ANY, "Nickname:");
    statusLabel = new wxStaticText(this, wxID_ANY, "Status:");
    stakeLabel = new wxStaticText(this, wxID_ANY, "Stake:");

    stake = new wxStaticText(this, wxID_ANY, std::to_string(0));
    status = new wxStaticText(this, wxID_ANY, "in game");//"in game");
    nickname = new wxStaticText(this, wxID_ANY, _nickname);
}


void StatusPanel::Arrange() {
    grid = new wxGridSizer(3, 2, 0, 0);
    grid->Add(nicknameLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
    grid->Add(nickname, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2);

    grid->Add(statusLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
    grid->Add(status, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2);

    grid->Add(stakeLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
    grid->Add(stake, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
}

void StatusPanel::SetCardsPanel(PlayerCardsPanel* _cardsPanel) {
    cardsPanel = _cardsPanel;
}

void StatusPanel::SetCards(std::array<struct Card, pocket_cards>& cards) {
    //cardsPanel->FillPocketCards(cards);
    //cardsPanel->Refresh();
}

void StatusPanel::SetCards(struct Card& c1, struct Card& c2) {
    cardsPanel->FillPocketCards(c1,c2);
    cardsPanel->Refresh();
}