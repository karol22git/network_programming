#pragma once
#include <wx/wx.h>
#include "InfoPanel.hpp"
class StatusBar: public InfoPanel{//public wxPanel {
    public:
        StatusBar(wxWindow* parent, wxPoint pos, wxSize size, const std::string&);
        void Arrange() override;
        void CreateItems(const std::string&) override;
        void SetWallet(int);
        void SetPot(const std::string&);
    private:
        wxStaticText* walletLabel;
        wxStaticText* wallet;
        wxStaticText* potLabel;
        wxStaticText* pot;
        //const int labelFlag = wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL;
        //const int flag = wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL;
        //const int margin = 2;
        const std::string usernameString = "Username: ";
        const std::string walletString = "Youre wallet: ";
        const std::string stakeString = "Current stake: ";
        const std::string potString = "Total pot: ";
};