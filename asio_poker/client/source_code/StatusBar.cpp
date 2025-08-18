#include "../include/StatusBar.hpp"


StatusBar::StatusBar(wxWindow* parent, wxPoint pos,  wxSize size, const std::string& _username): InfoPanel(parent, pos, size) {
    CreateItems(_username);
    Arrange();
    SetSizerAndFit(grid);
}

void StatusBar::CreateItems(const std::string& _username) {
    nicknameLabel =  new wxStaticText(this, wxID_ANY, usernameString);
    walletLabel = new wxStaticText(this, wxID_ANY, walletString);
    stakeLabel = new wxStaticText(this, wxID_ANY, stakeString);
    potLabel =  new wxStaticText(this, wxID_ANY, potString);
    wallet = new wxStaticText(this, wxID_ANY, std::to_string(start_money));
    nickname = new wxStaticText(this, wxID_ANY,_username);
    stake =  new wxStaticText(this, wxID_ANY, std::to_string(0));
    pot = new wxStaticText(this, wxID_ANY, std::to_string(0));
}

void StatusBar::Arrange() {
    grid = new wxGridSizer(4, 2, 0, 0);
    grid->Add(nicknameLabel, 0, labelFlag, margin);
    grid->Add(nickname, 0,flag, margin);

    grid->Add(walletLabel, 0, labelFlag, margin);
    grid->Add(wallet, 0,flag, margin);

    grid->Add(stakeLabel, 0,labelFlag, margin);
    grid->Add(stake, 0, flag, margin);
    grid->Add(potLabel, 0, labelFlag, margin);
    grid->Add(pot, 0,flag, margin);
}

void StatusBar::SetWallet(int _amount) {
    wallet->SetLabel(std::to_string(_amount));
}

void StatusBar::SetPot(const std::string& _pot) {
    pot->SetLabel(_pot);
}