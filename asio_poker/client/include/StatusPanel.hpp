#pragma once
#include <wx/wx.h>


class StatusPanel: public wxPanel {
    public:
        StatusPanel();
    private:
        wxStaticText* statusLabel;
        wxStatictext* moneyLabel;
};