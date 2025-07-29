#pragma once
#include <wx/wx.h>


class StatusPanel: public wxPanel {
    public:
        StatusPanel(wxWindow* parent, wxSize size,wxPoint pos);
    private:
        wxStaticText* statusLabel;
        wxStaticText* stakeLabel;
        wxStaticText* nicknameLabel;
        wxStaticText* nickname;
        wxStaticText* status;
        wxStaticText* stake;
};