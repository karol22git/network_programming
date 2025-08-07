#pragma once
#include <string>
#include <wx/wx.h>
class BindPanel: public wxPanel {
    public:
        BindPanel(wxWindow* parent, wxSize size,const std::string& title, const std::string&);
        void Arrange();
        void CreateItems(const std::string&, const std::string&);
    private:
        wxButton* actionButton;
        wxStaticText* infoField;
        wxBoxSizer* bindPanelSizer;
};