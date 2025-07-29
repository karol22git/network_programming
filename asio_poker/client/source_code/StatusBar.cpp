#include "../include/StatusBar.hpp"


StatusBar::StatusBar(wxWindow* parent, wxSize size): wxPanel(parent, wxID_ANY, wxDefaultPosition, size) {
    nicknameLabel =  new wxStaticText(this, wxID_ANY, "Username:");
    nickname = new wxStaticText(this, wxID_ANY, "John");
    walletLabel = new wxStaticText(this, wxID_ANY, "Youre wallet:");
    wallet = new wxStaticText(this, wxID_ANY, "150");
    stakeLabel = new wxStaticText(this, wxID_ANY, "Current stake: ");
    stake =  new wxStaticText(this, wxID_ANY, "200");

    wxGridSizer* grid = new wxGridSizer(4, 2, 0, 0); // odstępy między komórkami
    grid->Add(nicknameLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
    grid->Add(nickname, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2);

    grid->Add(walletLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
    grid->Add(wallet, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2);

    grid->Add(stakeLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
    grid->Add(stake, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
    grid->Add(20, 23, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
   // SetBackgroundColour(*wxRED);
    SetSizerAndFit(grid);
}