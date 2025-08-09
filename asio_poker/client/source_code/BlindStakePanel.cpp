#include "../include/BlindStakePanel.hpp"


BlindStakePanel::BlindStakePanel(wxWindow* parent, bool type): wxPanel(parent,wxID_ANY, wxDefaultPosition,wxDefaultSize) {
    label = new wxStaticText(this, wxID_ANY, labelString,wxDefaultPosition, wxSize(labelWidth ,labelHeight));
    placeholder = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(135,50));
    if(type) GenerateBigBlindPanel();
    else GenerateSmallBlindPanel();
    Arrange();
    SetSizerAndFit(sizer);
}

void BlindStakePanel::GenerateBigBlindPanel() {
    stake = new wxTextCtrl(this, wxID_ANY, bigBlindString, wxDefaultPosition, wxSize(stakeWidth,stakeheight), wxTE_READONLY);
    blindButton  = new wxButton(this, wxID_ANY, bigBlind,wxDefaultPosition,wxSize(150,50));
}

void BlindStakePanel::GenerateSmallBlindPanel() {
    stake = new wxTextCtrl(this, wxID_ANY, smallBlindString, wxDefaultPosition, wxSize(stakeWidth,stakeheight), wxTE_READONLY);
    blindButton  = new wxButton(this, wxID_ANY, smallBlind,wxDefaultPosition,wxSize(150,50));
}

void BlindStakePanel::Arrange() {
    sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(placeholder,0,wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);
    sizer->Add(blindButton,0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);
    sizer->Add(label,0, wxALIGN_CENTER | wxTOP | wxBOTTOM,20);
    sizer->Add(stake,0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);
}

wxButton* BlindStakePanel::GetBlindButton() {
    return blindButton;
}