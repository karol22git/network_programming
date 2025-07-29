#include "../include/StatusPanel.hpp"

StatusPanel::StatusPanel(wxWindow* parent, wxSize size, wxPoint pos)
    : wxPanel(parent, wxID_ANY, pos, size)
{
    wxGridSizer* grid = new wxGridSizer(3, 2, 0, 0); // odstępy między komórkami

    nicknameLabel = new wxStaticText(this, wxID_ANY, "Nickname:");
    nickname = new wxStaticText(this, wxID_ANY, "john deer");

    statusLabel = new wxStaticText(this, wxID_ANY, "Status:");
    status = new wxStaticText(this, wxID_ANY, "in game");

    stakeLabel = new wxStaticText(this, wxID_ANY, "Stake:");
    stake = new wxStaticText(this, wxID_ANY, "100");

    grid->Add(nicknameLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
    grid->Add(nickname, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2);

    grid->Add(statusLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
    grid->Add(status, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2);

    grid->Add(stakeLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
    grid->Add(stake, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
   // SetBackgroundColour(*wxRED);
    SetSizerAndFit(grid);
}
