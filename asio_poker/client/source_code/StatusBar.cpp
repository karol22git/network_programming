#include "../include/StatusBar.hpp"


StatusBar::StatusBar(wxWindow* parent, wxPoint pos,  wxSize size, const std::string& _username): InfoPanel(parent, pos, size) {
    CreateItems(_username);
    Arrange();
    SetSizerAndFit(grid);
}

void StatusBar::CreateItems(const std::string& _username) {
    nicknameLabel =  new wxStaticText(this, wxID_ANY, "Username:");
    walletLabel = new wxStaticText(this, wxID_ANY, "Youre wallet:");
    stakeLabel = new wxStaticText(this, wxID_ANY, "Current stake: ");

    wallet = new wxStaticText(this, wxID_ANY, std::to_string(start_money));
    nickname = new wxStaticText(this, wxID_ANY,_username);
    stake =  new wxStaticText(this, wxID_ANY, std::to_string(0));
}

void StatusBar::Arrange() {
    grid = new wxGridSizer(4, 2, 0, 0); // odstępy między komórkami
    grid->Add(nicknameLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
    grid->Add(nickname, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2);

    grid->Add(walletLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
    grid->Add(wallet, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2);

    grid->Add(stakeLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
    grid->Add(stake, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
    grid->Add(20, 23, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
}

void StatusBar::SetWallet(int _amount) {
    wallet->SetLabel(std::to_string(_amount));
}