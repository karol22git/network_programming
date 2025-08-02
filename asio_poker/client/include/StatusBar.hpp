#pragma once
#include <wx/wx.h>
#include "InfoPanel.hpp"
class StatusBar: public InfoPanel{//public wxPanel {
    public:
        StatusBar(wxWindow* parent, wxPoint pos, wxSize size, const std::string&);
        void Arrange() override;
        void CreateItems(const std::string&) override;
    private:
        wxStaticText* walletLabel;
        wxStaticText* wallet;
};