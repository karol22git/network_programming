#pragma once
#include <wx/wx.h>
#include "InfoPanel.hpp"

class StatusPanel: public InfoPanel{//public wxPanel {
    public:
        StatusPanel(wxWindow* parent, wxPoint pos, wxSize size, const std::string&);
        void Arrange() override;
        void CreateItems(const std::string&) override;
    private:
        wxStaticText* statusLabel;
        wxStaticText* status;
};