#include "../include/StatusPanel.hpp"

StatusPanel::StatusPanel(wxWindow* parent,  wxPoint pos, wxSize size, const std::string& _nickname)
    : InfoPanel(parent, pos, size)
{

    CreateItems( _nickname);
    Arrange();

    SetSizerAndFit(grid);
}

void StatusPanel::CreateItems(const std::string& _nickname) {
    nicknameLabel = new wxStaticText(this, wxID_ANY, nicknameString);
    statusLabel = new wxStaticText(this, wxID_ANY, statusString);
    stakeLabel = new wxStaticText(this, wxID_ANY, stakeString);

    stake = new wxStaticText(this, wxID_ANY, std::to_string(0));
    status = new wxStaticText(this, wxID_ANY, ingameString);//"in game");
    nickname = new wxStaticText(this, wxID_ANY, _nickname);
}


void StatusPanel::Arrange() {
    grid = new wxGridSizer(3, 2, 0, 0);
    grid->Add(nicknameLabel, 0, labelFlag, margin);
    grid->Add(nickname, 0, flag, margin);

    grid->Add(statusLabel, 0, labelFlag, margin);
    grid->Add(status, 0, flag, margin);

    grid->Add(stakeLabel, 0, labelFlag, margin);
    grid->Add(stake, 0, flag, margin);
}

void StatusPanel::SetCardsPanel(PlayerCardsPanel* _cardsPanel) {
    cardsPanel = _cardsPanel;
}

void StatusPanel::SetCards(std::array<struct Card, pocket_cards>& cards) {
}

void StatusPanel::SetCards(struct Card& c1, struct Card& c2) {
    cardsPanel->FillPocketCards(c1,c2);
    cardsPanel->Refresh();
}