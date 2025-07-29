#pragma once
#include <wx/wx.h>

class StatusBar: public wxPanel {
    public:
        StatusBar(wxWindow* parent, wxSize size);
    private:
        wxStaticText* nicknameLabel;
        wxStaticText* nickname;
        wxStaticText* walletLabel;
        wxStaticText* wallet;
        wxStaticText* stakeLabel;
        wxStaticText* stake;
};